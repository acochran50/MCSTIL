#ifndef _MCSTIL_ERROR_H
#define _MCSTIL_ERROR_H

namespace MCSTIL {
namespace ERROR {
/***************/

int FileNotFound();
int InvalidParams();
int InvalidTissue(int index);
void InvalidLayer();

}
}

#endif
