/**************************************************************************
 * Mode.cpp
 *
 *************************************************************************/
#include <Arduino.h>

#include "Mode.h"

CTRL_MODE_T m_CtrlMode;
boolean mIsJpMode = false;   //Japanese mode flag

CTRL_MODE_T MODE_getCurrentMode(void) {
  return m_CtrlMode;
}

CTRL_MODE_T MODE_setCurrentMode(CTRL_MODE_T ctrlMode) {
  m_CtrlMode = ctrlMode;
}

void MODE_setJpMode() {
  mIsJpMode = true;
}

void MODE_setEnglishMode() {
  mIsJpMode = false;
}

boolean MODE_isJpMode() {
  return mIsJpMode;
}
