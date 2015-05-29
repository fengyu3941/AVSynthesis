#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char** argv)
{
	cout<<"usage: AVSynthesis command.txt"<<endl;
	cout<<"The commond.txt is link below:"<<endl;
	cout<<"\t\t FinalVideoFile1.mpg|audio1.mp3"<<endl;
	cout<<"\t\t FinalVideoFile2.mpg|audio2.mp3"<<endl;
	cout<<"\t\t FinalVideoFile3.mpg|audio3.mp3"<<endl;

	if (argc<2)
	{
		cout<<"need 2 parameter at lease"<<endl;
		return -1;
	}

	ifstream infile;
	infile.open(argv[1],ios_base::in);
	if (!infile)
	{
		cout<<"can not open "<<argv[1]<<endl;
		return -1;
	}
	string videofilename;
	string audiofilename;
	string tempfilename;
	string extension;
	char str_line[1024];
	char command[1024];
	memset(command, 0, 1024);
	
	while(infile.good())
	{
		memset(str_line, 0, 1024);
		infile.getline(str_line, 1024);
	
		videofilename = strtok(str_line, "|");
		int pos = videofilename.find('.');
		if (pos == string::npos)
		{
			cout<<videofilename.c_str()<<"'s media type can not be detected"<<endl;
			continue;
		}
		extension = videofilename.substr(pos, videofilename.size()-pos+1);
		audiofilename = strtok(NULL, "|");
		tempfilename  = string("temp") + extension;
		cout<<"Start Synthesis "<<videofilename.c_str()<<" "<<audiofilename.c_str()<<endl;

		memset(command, 0, 1024);
		sprintf(command, "del %s", tempfilename.c_str());
		system(command);

		memset(command, 0, 1024);
		sprintf(command, "ffmpeg -i %s -vcodec copy -an %s", videofilename.c_str(), tempfilename.c_str());
		system(command);

		memset(command, 0, 1024);
		sprintf(command, "del %s", videofilename.c_str());
		system(command);

		memset(command, 0, 1024);
		sprintf(command,"ffmpeg -i %s -i %s  -vcodec copy -acodec copy %s", tempfilename.c_str(), audiofilename.c_str(), videofilename.c_str());
		system(command);

		memset(command, 0, 1024);
		sprintf(command, "del %s", tempfilename.c_str());
		system(command);
		
		cout<<"End Synthesis "<<videofilename.c_str()<<" "<<audiofilename.c_str()<<endl;
	}
	infile.close();
	cout<<argv[1]<<" Systhesis Completed"<<endl;
	return 1;
}