#include "show.h"

void ShowNum(int n,void (* ptr)())
{
   (* ptr)(n);
}

void ShowMessage(void (* ptr)())
{
    (* ptr)();
}
