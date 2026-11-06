#include <ui/debug_screen.hpp>
#include <game/player.hpp>
#include <render/text.hpp>
#include <input/input.hpp>
#include <window/window.hpp>

#include <glad/glad.h>

#include <array>
#include <cmath>
#include <format>
#include <regex>
#include <string>

#if defined(_WIN32)

    // Prevent Windows from defining min and max as macros
    #define NOMINMAX
    #include <Windows.h>
    #include <Psapi.h>
#elif defined(__APPLE__)
    #include <sys/resource.h>
    #include <sys/types.h>
    #include <sys/sysctl.h>
#elif defined(__linux__)
    #include <sys/resource.h>
    #include <sys/sysinfo.h>
#endif

#ifdef _MSC_VER
    #include <intrin.h>
#else
    #include <cpuid.h>
#endif

namespace ui {


DebugScreen::DebugScreen(engine::Renderer *renderer, engine::Window& window, engine::Clock& clock, game::Player& player) :
    displayDebug(false),
    clock(clock),
    fpsElapsed(0.0),
    fpsFrames(0),
    playerCam(player.getCamera()),
    roundedFps(0)
{
    leftPanelText = std::string("Minecraft 1.16 (1.16/vanilla)\n")
        + "{} fps\n"
        + "Integrated server @ 5ms ticks, 2 tx, 450 rx\n"  // TODO Hardcoded integrated server info
        // TODO Hardcoded as it is not implemented yet
        + "C: 5/2560 (s) D: 8, pC: 000, pU: 00, aB: 04\n"
        + "E: 5/130, B: 0\n"
        + "P: 103, T: 131\n"
        + "Client Chunk Cache: 441, 373\n"
        + "ServerChunkCache: 2522\n"
        + "minecraft:overworld FC: 0\n"
        + "\n"
        + "XYZ: {:.3f} / {:.3f} / {:.3f}\n"
        // TODO Hardcoded as it is not implemented yet
        + "Block: 0 0 0\n"
        + "Chunk: 0 0 0 in 0 4 0\n"
        + "Facing: {} (Towards {}) ({:.1f} / {:.1f})";

    // TODO Hardcoded Java version and bitnesss
    rightPanelText = std::string("Java: 1.8.0_51 64bit\n")
        + "Mem: {}% {}/{}MB\n"
        + "Allocated: {}% {}MB\n"
        + "\n"
        + "CPU: " + getCPUName() + "\n"
        + "\n"
        + "Display: " + getDisplayName() + "\n"
        + reinterpret_cast<const char*>(glGetString(GL_RENDERER)) + "\n"
        + getOpenGLProfile() + " " + getDriverVersion();

    leftPanel = renderer->addText(
        engine::Text(leftPanelText, 0.0f, window.getHeight() - 20, 2.0f)
    );

    rightPanel = renderer->addText(
        engine::Text(rightPanelText, window.getWidth(), window.getHeight() - 20, 2.0f)
    );

    rightPanel->setRightAligned(window.getWidth(), window.getHeight() - 20);

    leftPanel->setBackgroundColor({80, 80, 80, 80});

    rightPanel->setBackgroundColor({80, 80, 80, 80});
}


void DebugScreen::update(const engine::Input &input, engine::Window& window) {
    if (input.wasKeyPressed(engine::Key::F3)) {
        displayDebug = !displayDebug;
    }
    if (window.wasResized()) {
        leftPanel->setPos(0.0f, window.getHeight() - 20);
        rightPanel->setRightAligned(window.getWidth(), window.getHeight() - 20);
    }
    if (displayDebug) {
        leftPanel->show();
        rightPanel->show();
    }
    else {
        leftPanel->hide();
        rightPanel->hide();
    }

    const double deltaTime = clock.getDeltaTime();
    if (deltaTime > 0.0) {
        fpsElapsed += deltaTime;
        ++fpsFrames;
    }

    if (fpsElapsed >= 1.0) {
        // Elapse FPS over time so the display will be stable
        const double fps = static_cast<double>(fpsFrames) / fpsElapsed;

        roundedFps = std::round(fps);

        fpsElapsed = 0.0;
        fpsFrames = 0;
    }

    renderLeftPanel(roundedFps);
    renderRightPanel();
}

void DebugScreen::renderLeftPanel(const int fps) const {

    // Minecraft Facing:
    //
    // West:  -X
    // East:  +X
    // North: -Z
    // South: +Z

    const auto forward = playerCam.forward();

    const std::string facing =
        std::abs(forward.x) > std::abs(forward.z)
            ? (forward.x < 0 ? "West" : "East")
            : (forward.z < 0 ? "North" : "South");

    const std::string facingCoord =
        std::abs(forward.x) > std::abs(forward.z)
            ? (forward.x < 0 ? "negative X" : "positive X")
            : (forward.z < 0 ? "negative Z" : "positive Z");

    leftPanel->setText(std::vformat(
        leftPanelText,
        std::make_format_args(
            fps,
            playerCam.position.x,
            playerCam.position.y,
            playerCam.position.z,
            facing,
            facingCoord,
            playerCam.yaw,
            playerCam.pitch
        )
    ));
}

void DebugScreen::renderRightPanel() const {
    const auto memoryUsage = getMemoryUsage() / 1024;

    // Simply just using 25% of system memory to simulate JVM max memory
    const auto jvmMemory = std::round((getSystemMemory() / 1024) * 0.25f);
    const auto memoryUsagePercentage = std::round((memoryUsage / jvmMemory) * 100);

    // Simply just using 45% of JVM max memory to simulate JVM allocated memory
    const auto jvmAllocMemory = std::round(jvmMemory * 0.45f);
    const auto allocMemoryUsagePercentage = std::round((memoryUsage / jvmAllocMemory) * 100);

    rightPanel->setText(std::vformat(
        rightPanelText,
        std::make_format_args(
            memoryUsagePercentage,
            memoryUsage,
            jvmMemory,
            allocMemoryUsagePercentage,
            jvmAllocMemory
        )
        )
    );
}

std::size_t DebugScreen::getMemoryUsage() const {
    #if defined(_WIN32)
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            return pmc.WorkingSetSize / 1024;
        }
    #elif defined(__APPLE__) || defined(__linux__)
        struct rusage usage;
        if (getrusage(RUSAGE_SELF, &usage) == 0) {
            #ifdef __APPLE__
                return usage.ru_maxrss / 1024;
            #else
                return usage.ru_maxrss;
            #endif
        }
    #endif
    return 0;
}

std::size_t DebugScreen::getSystemMemory() const {
    #if defined(_WIN32)
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);

        if (GlobalMemoryStatusEx(&memInfo)) {
            return memInfo.ullTotalPhys / 1024;
        }
    #elif defined(__APPLE__)
        int64_t totalPhysMem = 0;
        size_t len = sizeof(totalPhysMem);
        
        int mib[2] = {CTL_HW, HW_MEMSIZE};

        if (sysctl(mib, 2, &totalPhysMem, &len, NULL, 0) == 0) {
            return totalPhysMem / 1024;
        }
    #elif defined(__linux__)
        struct sysinfo sysInfo;

        if (sysinfo(&sysInfo) == 0) {
            unsigned long long totalPhysMem = sysInfo.totalram;
            totalPhysMem *= sysInfo.mem_unit;

            return totalPhysMem / 1024;
        }
    #endif
    return 0;
}

std::string DebugScreen::getCPUName() const {
    std::array<int, 4> cpu_info = { 0 };
    char cpu_string[49];
    std::memset(cpu_string, 0, sizeof(cpu_string));

    #ifdef _MSC_VER
        __cpuid(cpu_info.data(), 0x80000000);
    #else
        __get_cpuid(0x80000000, 
            (unsigned int*)&cpu_info[0], (unsigned int*)&cpu_info[1], 
            (unsigned int*)&cpu_info[2], (unsigned int*)&cpu_info[3]);
    #endif

    unsigned int extended_ids = cpu_info[0];
    if (extended_ids < 0x80000004) {
        return "Unknown Processor (Extended IDs not supported)";
    }

    // Call CPUID with 0x80000002, 0x80000003, 0x80000004
    for (unsigned int i = 0x80000002; i <= 0x80000004; ++i) {
    #ifdef _MSC_VER
            __cpuid(cpu_info.data(), i);
    #else
            __get_cpuid(i, 
                (unsigned int*)&cpu_info[0], (unsigned int*)&cpu_info[1], 
                (unsigned int*)&cpu_info[2], (unsigned int*)&cpu_info[3]);
    #endif
        std::memcpy(cpu_string + (i - 0x80000002) * 16, cpu_info.data(), 16);
    }

    return std::string(cpu_string);
}

std::string DebugScreen::getDisplayName() const {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const char* name = glfwGetMonitorName(monitor);
    return std::string(name ? name : "Unknown");
}

std::string DebugScreen::getOpenGLProfile() const {
    const auto version = std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    GLint profileMask = 0;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profileMask);
    
    if (profileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) {
        return version + " Compatibility Profile Context";
    } else {
        return version + " Core Profile Context";
    }
}

std::string DebugScreen::getDriverVersion() const {
    const GLubyte* rawVersion = glGetString(GL_VERSION);
    if (!rawVersion) return "";

    std::string versionStr(reinterpret_cast<const char*>(rawVersion));

    std::regex versionRegex(R"((\d+\.\d+(?:\.\d+)*)\s*$)");
    std::smatch match;

    // Search from the end of the string
    if (std::regex_search(versionStr, match, versionRegex)) {
        return match[1].str();
    }

    size_t lastSpace = versionStr.find_last_of(' ');
    if (lastSpace != std::string::npos) {
        return versionStr.substr(lastSpace + 1);
    }

    return versionStr;
}

}  // namespace ui
