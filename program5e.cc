//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>
#include <string>

using namespace std;
using namespace CryptoPP;

int main(int argc, char *argv[]){
  //use the crypto library to decrypt a given file to a given outfile using a given password
  string pass = argv[1];
  FileSource f(argv[2], true, new DefaultDecryptorWithMAC(pass.c_str(), new FileSink(argv[3])));
  return 0;

}
