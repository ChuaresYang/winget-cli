// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once
#include "pch.h"
#include "winget/ExperimentalFeature.h"
#include "winget/UserSettings.h"

namespace AppInstaller::Settings
{
    bool ExperimentalFeature::IsEnabled(Feature feature)
    {
        switch (feature)
        {
        case Feature::None:
            return true;
        case Feature::ExperimentalCmd:
            // ExperimentalArg depends on ExperimentalCmd, so instead of failing we could
            // assume that if ExperimentalArg is enabled then ExperimentalCmd is as well.
            return User().Get<Setting::EFExperimentalCmd>() || User().Get<Setting::EFExperimentalArg>();
        case Feature::ExperimentalArg:
            return User().Get<Setting::EFExperimentalArg>();
        default:
            THROW_HR(E_UNEXPECTED);
        }
    }

    ExperimentalFeature ExperimentalFeature::GetFeature(ExperimentalFeature::Feature feature)
    {
        switch (feature)
        {
        case Feature::ExperimentalCmd:
            return ExperimentalFeature{ "Command Sample", "experimentalCmd", "https://aka.ms/winget-settings", Feature::ExperimentalCmd };
        case Feature::ExperimentalArg:
            return ExperimentalFeature{ "Argument Sample", "experimentalArg", "https://aka.ms/winget-settings", Feature::ExperimentalArg };
        default:
            THROW_HR(E_UNEXPECTED);
        }
    }

    std::vector<ExperimentalFeature> ExperimentalFeature::GetAllFeatures()
    {
        std::vector<ExperimentalFeature> result;

        for (Feature_t i = 0x1; i < static_cast<Feature_t>(Feature::Max); i = i << 1)
        {
            result.emplace_back(GetFeature(static_cast<Feature>(i)));
        }

        return result;
    }
}
