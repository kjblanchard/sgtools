#include <sgtools/log.h>
int main() {
	sgInitializeLogSystem("testlog");
	int n = 1;
	float f = 0.14f;
	const char* name = "Hello!";
	sgSetLogLevel(sgLogLevelWarn);
	sgLogDebug("Whatthe %d, %f, %s", n, f, name);
	sgLogInfo("Whatthe %d, %f, %s", n, f, name);
	sgLogWarn("Whatthe %d, %f, %s", n, f, name);
	sgLogError("Whatthe %d, %f, %s", n, f, name);
	sgLogCritical("Whatthe %d, %f, %s", n, f, name);
}
