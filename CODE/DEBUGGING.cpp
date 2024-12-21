

#ifdef DEBUGGING
#ifndef ENGINE_DEBUGGING_CPP
#define ENGINE_DEBUGGING_CPP

#include "CONFIG.hpp"

namespace ENGINE_DEBUGGING {
	/*
		CONSOLE SYNTAX:
			WORDS ARE SEPARATED BY ;

			EXAMPLE: window;name;new window name
			THE FIRST WORD (window) IDENTIFIES THE CLASS TO BE ADDRESSED
			THE SECOND WORD (name) IDENTIFIES THE KEY TO BE ADDRESSED
			THE THIRD WORD (new window name) IDENTIFIES THE VALUE TO BE SETTED

			CLASSES:
				window					- engine window
				|	KEYS:
						name				- window name
						res					- window resolution
				|		render
						|	KEYS:
								ogl				- open gl
				|		|		|	KEYS:
								|
				objects					- models
				|	KEYS:
						* (+ 1)				- select model (and add 1 to model position, ex. you want to access model with pos. 0 you need to enter 1)
						|	KEYS:
				|				pos				- position
								* (+ 1)			- select voxel (and add 1 to voxel position, ex. you want to access voxel with pos. 0 you need to enter 1)
				|		|		|	KEYS:
								|		pos			- position
						|		|		rot			- rotation
				|				|		col			- color
						|		|
				pobjects				- polygon models
				|	KEYS:
						* (+ 1)				- select model (and add 1 to model position, ex. you want to access model with pos. 0 you need to enter 1)
						|	KEYS:
				|				pos				- position
						|		* (+ 1)			- select voxel (and add 1 to voxel position, ex. you want to access voxel with pos. 0 you need to enter 1)
								|	KEYS:
				|		|		|		fpos		- first position
								|		spos		- second position
						|		|		col			- color
				|				|
	*/

	//MODIFIED CODE BY "Vincenzo Pii" ON https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	vector<string> split(string str, string delimiter) {
		vector<string> tokens;
		size_t pos = 0;
		string token;
		while ((pos = str.find(delimiter)) != string::npos) {
			token = str.substr(0, pos);
			tokens.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		tokens.push_back(str);

		return tokens;
	}

	void run()
	{
		while (true)
		{
			try
			{
				string input;
				cin >> input;

				ENGINE_FILE::save_in_log("exit.log", "Entered command: " + input);

				vector<string> splitted_input = split(input, ";");

				if (splitted_input[0] == "objects")
				{
					if (atoi(splitted_input[1].data()) > 0)
					{
						if (atoi(splitted_input[2].data()) > 0)
						{
							if (splitted_input[3] == "pos")
							{
								Vector3f pos = Vector3f(stof(splitted_input[4]), stof(splitted_input[5]), stof(splitted_input[6]));
								ENGINE_MODEL::models.at(stoi(splitted_input[1]) - 1)->voxels.at(stoi(splitted_input[2]) - 1).position = pos;
							}
							else if (splitted_input[3] == "rot")
							{
								Vector3f rot = Vector3f(stof(splitted_input[4]), stof(splitted_input[5]), stof(splitted_input[6]));
								ENGINE_MODEL::models.at(stoi(splitted_input[1]) - 1)->voxels.at(stoi(splitted_input[2]) - 1).rotation = rot;
							}
							else if (splitted_input[3] == "col")
							{
								Color col = Color(stof(splitted_input[4]), stof(splitted_input[5]), stof(splitted_input[6]));
								ENGINE_MODEL::models.at(stoi(splitted_input[1]) - 1)->voxels.at(stoi(splitted_input[2]) - 1).color = col;
							}
						}
						else if (splitted_input[2] == "pos")
						{
							Vector3f pos = Vector3f(stof(splitted_input[3]), stof(splitted_input[4]), stof(splitted_input[5]));
							ENGINE_MODEL::models.at(stoi(splitted_input[1]) - 1)->position = pos;
						}

						//ERROR
						else { cout << "Key do not exist" << endl; }
					}

					//ERROR
					else { cout << "Key do not exist" << endl; }
				}
				else if (splitted_input[0] == "pobjects")
				{
					if (atoi(splitted_input[1].data()) > 0)
					{
						if (atoi(splitted_input[2].data()) > 0)
						{

							if (splitted_input[3] == "fpos")
							{
								Vector3f pos = Vector3f(stof(splitted_input[4]), stof(splitted_input[5]), stof(splitted_input[6]));
								ENGINE_MODEL::polygon_models.at(stoi(splitted_input[1]) - 1)->polygon_voxels.at(stoi(splitted_input[2]) - 1).first_position = pos;
							}
							else if (splitted_input[3] == "spos")
							{
								Vector3f pos = Vector3f(stof(splitted_input[4]), stof(splitted_input[5]), stof(splitted_input[6]));
								ENGINE_MODEL::polygon_models.at(stoi(splitted_input[1]) - 1)->polygon_voxels.at(stoi(splitted_input[2]) - 1).second_position = pos;
							}
							else if (splitted_input[3] == "col")
							{
								Color col = Color(stoi(splitted_input[4]), stoi(splitted_input[5]), stoi(splitted_input[6]));
								ENGINE_MODEL::polygon_models.at(stoi(splitted_input[1]) - 1)->polygon_voxels.at(stoi(splitted_input[2]) - 1).color = col;
							}

							//ERROR
							else { cout << "Key do not exist" << endl; }
						}
						else if (splitted_input[2] == "pos")
						{
							Vector3f pos = Vector3f(stof(splitted_input[3]), stof(splitted_input[4]), stof(splitted_input[5]));
							ENGINE_MODEL::polygon_models.at(stoi(splitted_input[1]) - 1)->position = pos;
						}

						//ERROR
						else { cout << "Key do not exist" << endl; }
					}

					//ERROR
					else { cout << "Key do not exist" << endl; }
				}
				else if (splitted_input[0] == "window")
				{
					if (splitted_input[1] == "name")
					{
						ENGINE_CONFIG::WINDOW_NAME = splitted_input[2];
						ENGINE_CONFIG::SFML_WINDOW.setTitle(splitted_input[2]);
					}
					else if (splitted_input[1] == "render")
					{
						if (splitted_input[2] == "ogl")
						{
						}

						//ERROR
						else { cout << "Key do not exist" << endl; }
					}

					//ERROR
					else { cout << "Key do not exist" << endl; }
				}

				//ERROR
				else { cout << "Class do not exist" << endl; }
			}
			catch (char* error)
			{
				string error_str;
				for (int i = 0; i < strlen(error); i++)
				{
					error_str += error[i];
				}

				cout << "Catched error with code: " << error_str << endl;

				ENGINE_FILE::save_in_log("exit.log", "Catched error with code: " + error_str);
			}
		}
	}
}

#endif // ENGINE_DEBUGGING_CPP
#endif