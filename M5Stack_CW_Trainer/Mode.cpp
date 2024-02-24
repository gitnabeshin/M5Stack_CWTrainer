/**************************************************************************
 * Mode.cpp
 *
 *************************************************************************/
#include <Arduino.h>

#include "Mode.h"

CTRL_MODE_T m_CtrlMode;
INPUT_METHOD_T m_InputMethod;
boolean mIsJpMode = false;   //Japanese mode flag

CTRL_MODE_T MODE_getCurrentMode(void) {
  return m_CtrlMode;
}

void MODE_setCurrentMode(CTRL_MODE_T ctrlMode) {
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

void MODE_setInputMethod(INPUT_METHOD_T inputMethod) {
  m_InputMethod = inputMethod;
}

INPUT_METHOD_T MODE_getInputMethod(void) {
  return m_InputMethod;
}
