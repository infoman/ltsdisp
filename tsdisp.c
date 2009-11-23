#include <stdio.h>
#include <dlfcn.h>
#include "TsRemoteImport.h"

int main() {
	if (!InitTsRemoteLibrary(0)) {
		tsrQuit();
		return 0;
	}
	return 1;
}
