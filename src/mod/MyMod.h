#pragma once

#include "ll/api/mod/NativeMod.h"
#include "ll/api/io/Logger.h"

namespace NoRainFog {

class NoRainFog {
public:
    // Singleton access method
    static NoRainFog& getInstance();

    // Returns the NativeMod instance associated with this plugin
    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }
    
    // Returns the logger for this plugin
    [[nodiscard]] ll::io::Logger& getLogger() const { return *mLogger; }

    // --- Lifecycle Methods ---
    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();

private:
    // Private constructor to enforce singleton pattern
    NoRainFog();

    ll::mod::NativeMod& mSelf;
    ll::io::Logger* mLogger;
};

} // namespace NoRainFog
