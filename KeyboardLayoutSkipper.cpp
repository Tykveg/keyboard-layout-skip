#include "KeyboardLayoutSkipper.h"

void KeyboardLayoutSkipper()
{
	const size_t ARR_MAX = 100;
	HWND hwnd;
	DWORD threadID = 0;
	HKL layout;
	HKL layouts[ARR_MAX];
	size_t layouts_k = GetKeyboardLayoutList(ARR_MAX, layouts);
	if (layouts_k == 0 || layouts_k > ARR_MAX)
	{
		std::cout << "Error: something is really wrong with your keyboard layouts or you have more than" << ARR_MAX << " layouts. size_t layouts_k is " << layouts_k << std::endl;
		return;
	}
	std::cout << "Printing your layouts...\n";
	for (size_t i = 0; i < layouts_k; i++)
		std::cout << std::hex << (DWORD)layouts[i] << std::endl;

	if (layouts_k < 2)
	{
		std::cout << "I don't think you need this because you have less than 2 keyboard layouts.\n";
		return;
	}

	DWORD delay = 50;

	HKL skips[ARR_MAX];
	HKL skips_to[ARR_MAX];
	size_t skips_k = 0;

	std::ifstream f;
	f.open("config.txt");
	if (f)
	{
		std::cout << "Reading config.txt...\n";
		std::string line;
		while (std::getline(f, line))
		{
			if (line.rfind("//", 0) == 0)
				continue;
			std::cout << line << std::endl;
			size_t endname = line.find('=');
			if (line.substr(0, endname) == "delay")
			{
				line.erase(0, endname + 1);
				std::istringstream iss(line);
				DWORD tmp = 0;
				if (!(iss >> tmp))
				{
					std::cout << "Error writing DWORD delay. Skipping...\n";
				}
				else
				{
					delay = tmp;
				}
			}
		}
		std::cout << "Done reading config.txt\n";
		f.close();
	}
	else
	{
		std::cout << "Ignoring config.txt (not found)\n";
		std::cout << "delay=" << delay << std::endl;
	}

	f.open("skips.txt");
	if (f)
	{
		std::cout << "Reading skips.txt...\n";
		std::string line;
		while (std::getline(f, line))
		{
			if (line.rfind("//", 0) == 0)
				continue;
			std::cout << line << std::endl;
			DWORD tmp = 0;
			std::istringstream iss(line);
			if (iss >> std::hex >> tmp)
			{
				if (skips_k < ARR_MAX)
				{
					skips[skips_k++] = (HKL)tmp;
				}
				else
				{
					std::cout << "Error: more than " << ARR_MAX << " lines in skips.txt. Closing...\n";
					break;
				}
			}
			else
			{
				std::cout << "Error writing " << line << " as hex. Skipping...\n";
			}
		}
		std::cout << "Done reading skips.txt\n";
		f.close();
	}
	else if ((!f) || (skips_k < 1)) // but if (!f) then (skips_k < 1) is always true.
	{
		if (!f)
			std::cout << "skips.txt not found. ";
		else if (skips_k < 1)
			std::cout << "No correct skips found. ";
		std::cout << "Applying 0x04090409 (en_US) by default.\n";
		skips[0] = (HKL)0x04090409;
		skips_k = 1;
	}
	for (size_t i = 0; i < skips_k; i++)
	{
		bool found = false;
		for (size_t j = 0; j < layouts_k; j++)
		{
			if (skips[i] == layouts[j])
			{
				found = true;
				if ((j + 1) < layouts_k)
					skips_to[i] = layouts[j + 1];
				else
					skips_to[i] = layouts[0];
				break;
			}
		}
		if (!found)
		{
			std::cout << std::hex << (DWORD)skips[i] << " not found in your keyboard layout list. Consider delete that from skips.txt.\n";
			if (skips_k > 1)
			{
				size_t tmp_offset = 0;
				skips_k--;
				for (size_t j = 0; j < skips_k; j++)
				{
					if (i == j)
						tmp_offset++;
					skips[j] = skips[j + tmp_offset];
				}
				i--;
			}
			else
			{
				std::cout << "Error: too many skips that are not found in your layout list. Can't continue properly. Exiting...\n";
				return;
			}
		}
	}
	for (size_t i = 0; i < skips_k; i++)
	{
		for (size_t j = 0; j < skips_k; j++)
		{
			if (skips_to[i] == skips[j])
			{
				skips_to[i] = skips_to[j];
				i--;
				break;
			}
		}
	}
	for (size_t i = 0; i < skips_k; i++)
		std::cout << std::hex << (DWORD)skips[i] << " -> " << (DWORD)skips_to[i] << std::endl;
	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
	while (true)
	{
		Sleep(delay);
		hwnd = GetForegroundWindow();
		if (hwnd)
		{
			threadID = GetWindowThreadProcessId(hwnd, NULL);
			layout = GetKeyboardLayout(threadID);
			for (size_t i = 0; i < skips_k; i++)
				if (layout == skips[i])
				{
					//std::cout << "DETECTED!\n";
					PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 1, (DWORD)skips_to[i]);
				}
		}
	}
}