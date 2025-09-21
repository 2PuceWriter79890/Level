#include "MyMod.h" // Include our new header

#include "ll/api/memory/Hook.h"
#include "ll/api/mod/RegisterHelper.h"

#include "mc/world/level/Weather.h"
#include "mc/world/level/dimension/Dimension.h"
#include "mc/world/level/dimension/VanillaDimensions.h"

namespace NoRainFog {

// --- Singleton Implementation ---
NoRainFog& NoRainFog::getInstance() {
    // This static instance is created only once
    static NoRainFog instance;
    return instance;
}

// --- Constructor and Lifecycle Methods Implementation ---
NoRainFog::NoRainFog() : mSelf(*ll::mod::NativeMod::current()), mLogger(nullptr) {}

bool NoRainFog::load() {
    // Get and store the logger from the NativeMod instance
    mLogger = &getSelf().getLogger();
    return true;
}

bool NoRainFog::enable() {
    getLogger().info("NoRainFog Plugin enabled: Overworld rain fog has been removed.");
    return true;
}

bool NoRainFog::disable() {
    getLogger().info("NoRainFog Plugin disabled.");
    return true;
}

} // namespace NoRainFog


// --- Hook and Registration (Global Scope) ---

// The auto-hooking macro remains the best way to manage the hook's lifecycle.
// It is independent of our class structure and activates when the DLL is loaded.
LL_AUTO_TYPE_INSTANCE_HOOK(
    WeatherServerTickHook,
    ll::memory::HookPriority::Normal,
    Weather,
    "?serverTick@Weather@@QEAAXXZ",
    void,
    Weather* self
) {
    origin(self); // Call the original function

    Dimension& dimension = self->mDimension;
    if (dimension.getDimensionId() == VanillaDimensions::Overworld()) {
        self->mFogLevel = 0.0f;
    }
}

// Register the mod using the singleton instance.
LL_REGISTER_MOD(NoRainFog::NoRainFog, NoRainFog::NoRainFog::getInstance());
