#include <thread>
#include <cstring>
#include <unistd.h>

#include "network/multirecieve.h"

int main(){
	multirecieve(14000, "228.1.2.3", "192.168.5.1");
}
