#include "customdial.h"

CustomDial::CustomDial()
{
  setNotchesVisible(true);
  setMinimum(0);
  setMaximum(360);

  setWrapping(true);
  setSingleStep(45);
  setPageStep(90);
}

