#include "MyMod.h"

#include "ll/api/memory/Hook.h"
#include "ll/api/mod/RegisterHelper.h"
#include "ll/api/memory/Symbol.h" // 为 "_sym" 字面量提供定义

#include "mc/world/level/Weather.h"
#include "mc/world/level/dimension/Dimension.h"
#include "mc/world/level/dimension/VanillaDimensions.h"

// 引入字面量所在的命名空间
using namespace ll::literals::memory_literals;

namespace NoRainFog {

NoRainFog& NoRainFog::getInstance() {
    static NoRainFog instance;
    return instance;
}

NoRainFog::NoRainFog() : mSelf(*ll::mod::NativeMod::current()), mLogger(nullptr) {}

bool NoRainFog::load() {
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


// --- Hook and Registration ---

LL_AUTO_TYPE_INSTANCE_HOOK(
    WeatherServerTickHook,
    ll::memory::HookPriority::Normal,
    Weather,
    "?serverTick@Weather@@QEAAXXZ"_sym, // <--- 已修正：使用 "_sym" 字面量创建 SymbolView
    void,
    Weather* self
) {
    origin(self); 

    Dimension& dimension = self->mDimension;
    if (dimension.getDimensionId() == VanillaDimensions::Overworld()) {
        self->mFogLevel = 0.0f;
    }
}

// 注册插件
LL_REGISTER_MOD(NoRainFog::NoRainFog, NoRainFog::NoRainFog::getInstance());
