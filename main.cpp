#include "DBXV2/Xv2SavFile.h"
#include "debug.h"

bool change_ownership(const std::string &file)
{
	Xv2SavFile sav;
	uint64_t new_id; 
	char str[256];
	
	if (!sav.LoadFromFile(file))
	{
		DPRINTF("Failed to load file.\n");
		return false;
	}
	
	DPRINTF("Current SteamID 64 of file: %I64u\n", sav.GetSteamID64());
	DPRINTF("Enter a new one: ");
	// scanf is not working with %I64....
	fgets(str, sizeof(str), stdin);
	new_id = Utils::GetUnsigned64(str);
	
	sav.SetSteamID64(new_id);
		
	if (!sav.SaveToFile(file))
	{
		DPRINTF("Failed saving file.\n");
		return false;
	}
	
	UPRINTF("New SteamID 64 succesfully set to %I64u\n", new_id);	
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		DPRINTF("Usage: %s file.sav\n", argv[0]);
		return -1;
	}
	
	change_ownership(argv[1]);
	
	UPRINTF("Press enter to exit.");
    getchar();
	
	return 0;
}
