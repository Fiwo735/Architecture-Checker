// IMPORTANT
// The content of machinecodes.csv uses and modifies some of the information found on:
// http://www.sco.com/developers/gabi/latest/ch4.eheader.html

#include <iostream>
#include <fstream>
#include <string>
#include <map>

// function used for loading e_machine values and their meanings
void loadMachineCodes(std::string filename, std::map<int, std::string>& machineCodes);

int main(int argc, char *argv[]){

  // handling wrong number of input files
  if(argc != 2){
    std::cerr << "Expected 1 input filename" << std::endl;
    std::exit(1);
  }

  // opening ELF file
  std::string elfName = argv[1];
  std::ifstream elfStream (elfName, std::ios::binary);

  // handling error with opening elfStream
  if(!elfStream.is_open()){
    std::cerr << elfName << " cannot be opened" << std::endl;
    std::exit(1);
  }

  // calculating ELF size
  elfStream.seekg(0, std::ios::end);
  int elfSize = elfStream.tellg();
  elfStream.seekg(0, std::ios::beg);

  // extracting content of ELF as binary into char array
  char* buffer = new char[elfSize];
  elfStream.read(buffer, elfSize);
  elfStream.close();

  // getting e_machine field value
  // other fields can be found in the same way, thats why all data is extracted from ELF
  uint32_t e_machine = static_cast<uint32_t>(buffer[18]) & 0xFF;
  delete[] buffer;

  // loading e_machine values and their meanings
  std::map<int, std::string> machineCodes;
  loadMachineCodes("machinecodes.csv", machineCodes);

  // finding the corresponding architecture
  std::cout << machineCodes[e_machine] << std::endl;

  return 0;
}

void loadMachineCodes(std::string filename, std::map<int, std::string>& machineCodes){

  // opening file
  std::fstream codeFile;
  codeFile.open(filename, std::ios::in);

  // handling error with opening codeFile
  if(!codeFile.is_open()){
    std::cerr << filename << " cannot be opened" << std::endl;
    std::exit(1);
  }

  // extracting e_machine values and their meaning from CSV file
  std::string row;
  while(std::getline(codeFile, row)){
    int i = 0;
    std::string value;
    while(row[i] != ','){
      value += row[i];
      i++;
    }
    i++;

    std::string machine;
    while(i < row.length()){
      machine += row[i];
      i++;
    }
    machineCodes[stoi(value)] = machine;
  }
}
