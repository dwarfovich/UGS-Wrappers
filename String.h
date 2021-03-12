#pragma once

#ifdef USE_CSTD_STRING
#include "CStdString.h"
#define CString CStdString
#else
#include <atlstr.h>
#endif
