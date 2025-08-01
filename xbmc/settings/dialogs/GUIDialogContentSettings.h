/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/Scraper.h"
#include "settings/dialogs/GUIDialogSettingsManualBase.h"

#include <map>
#include <utility>

namespace KODI::VIDEO
{
  struct SScanSettings;
}
class CFileItemList;

class CGUIDialogContentSettings : public CGUIDialogSettingsManualBase
{
public:
  CGUIDialogContentSettings();

  // specialization of CGUIWindow
  bool HasListItems() const override { return true; }

  ADDON::ContentType GetContent() const { return m_content; }
  void SetContent(ADDON::ContentType content);
  void ResetContent();

  const ADDON::ScraperPtr& GetScraper() const { return m_scraper; }
  void SetScraper(ADDON::ScraperPtr scraper) { m_scraper = std::move(scraper); }

  void SetScanSettings(const KODI::VIDEO::SScanSettings& scanSettings);
  bool GetScanRecursive() const { return m_scanRecursive; }
  bool GetUseDirectoryNames() const { return m_useDirectoryNames; }
  bool GetContainsSingleItem() const { return m_containsSingleItem; }
  bool GetExclude() const { return m_exclude; }
  bool GetNoUpdating() const { return m_noUpdating; }
  bool GetUseAllExternalAudio() const { return m_allExternalAudio; }

  static bool Show(ADDON::ScraperPtr& scraper,
                   ADDON::ContentType content = ADDON::ContentType::NONE);
  static bool Show(ADDON::ScraperPtr& scraper,
                   KODI::VIDEO::SScanSettings& settings,
                   ADDON::ContentType content = ADDON::ContentType::NONE);

protected:
  // implementations of ISettingCallback
  void OnSettingChanged(const std::shared_ptr<const CSetting>& setting) override;
  void OnSettingAction(const std::shared_ptr<const CSetting>& setting) override;

  // specialization of CGUIDialogSettingsBase
  bool AllowResettingSettings() const override { return false; }
  bool Save() override;
  void SetupView() override;

  // specialization of CGUIDialogSettingsManualBase
  void InitializeSettings() override;

private:
  void SetLabel2(const std::string &settingid, const std::string &label);
  void ToggleState(const std::string &settingid, bool enabled);
  using CGUIDialogSettingsManualBase::SetFocus;
  void SetFocusToSetting(const std::string& settingid);

  /*!
  * @brief The currently selected content type
  */
  ADDON::ContentType m_content{ADDON::ContentType::NONE};
  /*!
  * @brief The selected content type at dialog creation
  */
  ADDON::ContentType m_originalContent{ADDON::ContentType::NONE};
  /*!
  * @brief The currently selected scraper
  */
  ADDON::ScraperPtr m_scraper;

  bool m_showScanSettings = false;
  bool m_scanRecursive = false;
  bool m_useDirectoryNames = false;
  bool m_containsSingleItem = false;
  bool m_exclude = false;
  bool m_noUpdating = false;
  bool m_allExternalAudio = false;
};
