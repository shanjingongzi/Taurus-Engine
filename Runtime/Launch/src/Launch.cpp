
void EnginePreInit(const char *cmdLine)
{
	int32 errorLevel=GEngineLoop::PreInit(cmdLine);
	return errorLevel;
}

void EngineTick()
{
//	GEngineLoop.Tick();
}

int GuardeMain(const char* cmdLine)
{
	int32 errorLevel=EnginePreInit(cmdLine);
	EngineTick();
	return 1;
}
