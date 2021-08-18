
	// attempt to use setMsgListA ... maybe to be kept for syntax reminder ?
	// char args[1000];
	// argListFormatter(msg->getClassId(), 101, 2, 1, args, "%s%s%s%s%s%s", "[FAULT_toBeRetrieveFromDB]", "seproDBParam1", "seproDBParam2", "seproDBParam3", "seproDBParam4", "seproDBParam5");  

void	argListFormatter(BPApiRepSysMsgClass classId, uint32_t compNr, uint32_t instNr, uint32_t msgNr, char *dest, const char *formatted_str, ...)
{
	va_list argList;
	va_start(argList, formatted_str);
	vsprintf(dest, formatted_str, argList);
	va_end(argList);

	BPApiRepSysSetMsgListA(classId, compNr, instNr, msgNr, formatted_str, argList); 
}