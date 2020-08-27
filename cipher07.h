/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER07_H
#define CIPHER07_H

#include <cstring>
#include <math.h>
#include <vector>

using namespace std;

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher07 : public Cipher
{
public:
   virtual std::string getPseudoAuth()  { return "Nimesh Subedi"; }
   virtual std::string getCipherName()  { return "Tap Code"; }
   virtual std::string getEncryptAuth() { return "Nimesh Subedi"; }
   virtual std::string getDecryptAuth() { return "Nimesh Subedi"; }

   /***********************************************************
    * GET CIPHER CITATION
    * Returns the citation from which we learned about the cipher
    ***********************************************************/
   virtual std::string getCipherCitation()
   {
        std::string citation;
        citation = "https://www.braingle.com/brainteasers/codes/tapcode.php\n";
        citation += "https://www.boxentriq.com/code-breaking/tap-code\n";
        citation += "https://www.pbs.org/wgbh/americanexperience/features/honor-tap-code/\n";
        
        return std::string(citation);
   }
   
   /**********************************************************
    * GET PSEUDOCODE
    * Returns the pseudocode as a string to be used by the caller.
    **********************************************************/
   virtual std::string getPseudocode()
   {
      std::string str;

      // TODO: please format your pseudocode
      // The encrypt pseudocode
      str =  "define encrypt(message, key):\n";
      str += "       convert the string into a character array so it can beused to loop through every letter.\n";
      str += "       use the ascii table to determine the number of character that are going to be used.\n";
      str += "           substract 33 and divide it by 10 to recieve the row\n";
      str += "           substract 33 and use MOD 10 to recieve the column\n";
      str += "       add the dots for the number of rows\n";
      str += "       add a space between the rol and the column";
      str += "       add the dots for the number of columns\n";
      str += "       add a double space after every letter\n";
      str += "       add backlash for a space\n";
      str += "    return the encrypted string\n";

      // The decrypt pseudocode
      str += "define decrypt(message, key):\n";
      str += "       make a split function so it can be used to split the characters in the begenning\n";
      str += "       Replace the Backlash with A single space.\n";
      str += "       and the split the string again to get the row and column of each character.\n";
      str += "           substract 1 from the row and multiply it by 10 to recieve the first digit\n";
      str += "           substract 1 to recieve the second digit\n";
      str += "           add both the first and the second digit and add 33 to get the ascii value\n";
      str += "       convert each ascii value to the coresponding character";
      str += "       concatinate the characters to create a string\n";
      str += "    return the decrypted string\n";

      return str;
   }

   /**********************************************************
    * ENCRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string encrypt(const std::string & plainText,
                               const std::string & password)
   {
      std::string cipherText = plainText;
      std::string tapCode = "";
      
      for (int i = 0; i < cipherText.length(); i++) {

         if (cipherText[i] == ' ')
         {
            tapCode += "/  ";
            continue;
         }
         
         int first = floor(((int)cipherText[i] - 33) / 10);
         int second = ((int)cipherText[i] - 33) % 10;
         for (int j = 0; j <= first; j++) {
            tapCode += "."; 
         }
         tapCode += " ";
         for (int k = 0; k <= second; k++) {
            tapCode += "."; 
         }
         if (i != cipherText.length()-1) {
            tapCode += "  ";
         }
      }
      cipherText = tapCode;
      return cipherText;
   }

   /**********************************************************
    * DECRYPT
    * TODO: ADD description
    **********************************************************/
   virtual std::string decrypt(const std::string & cipherText,
                               const std::string & password)
   {
      std::string plainText = cipherText;
      std::string tapDecode = "";
      int first = 0;
      int second = 0;

      vector<string> splitArr = split(plainText, "  ");

      for (int i = 0; i < splitArr.size(); i++) {
         if (splitArr[i] == "/") {
            tapDecode += " ";
            continue;
         }

         vector<string> splitedArr = split(splitArr[i], " ");

         first = splitedArr[0].length();
         second = splitedArr[1].length();
         first = (first - 1) * 10;
         second = second - 1;
         int total = (first + second) + 33;
         
         tapDecode += (char)total;
      }
      plainText = tapDecode;
      return plainText;
   }

   private:

   vector<string> split(string input, string delimiter) {
      size_t found;
      int count = 0;
      vector<string> splitArr;
      string singleValue;
      do {
         found = input.find(delimiter);
         if (found != -1) {
            singleValue = input.substr (0, found);
            splitArr.push_back(singleValue);
            //find next delimeter
            //if delimiter found, put value from end of last delimiter to this delimeter
            input = input.substr(found + delimiter.length(), input.length());
         } else {
            splitArr.push_back(input);
            count = 1;
         }
         
      } while (count != 1);
      
      return splitArr;
   }
};

#endif // CIPHER07_H