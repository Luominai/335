#include "File.hpp"
#include "Folder.hpp"

int main() {
    // // others
    // int array[4];
    // int* pointer = array;
    // std::cout << "size of array is " << sizeof(array) << std::endl;
    // std::cout << "size of pointer to array is " << sizeof(pointer) << std::endl;
    // std::cout << std::endl;

    // default constructor
    // File file1;
    // std::cout << file1 << std::endl;
    // std::cout << std::endl;

    // parameterized constructor
    // int* array2 = new int[256];
    // File file2(".env", "hello world world", array2); // should have the name .env
    // File file2("txt.txt.txt", "hello", array2);      // should throw
    // File file2("a", "hello", array2);                // should append .txt
    // File file2("a.", "hello", array2);               // should append txt
    // File file2("", "hello", array2);                 // should default to NewFile.txt
    // std::cout << file2 << std::endl;
    // std::cout << std::endl;

    // copy constructor
    // // File file2;
    // // int array2[4];
    // // File file2("text.txt", "hello world world", array2);
    // File file3(file2);
    // std::cout << file3 << std::endl;
    // std::cout << std::endl;

    // // copy assignment
    // File file4;
    // file4 = file4;                                   // should skip
    // file4 = file3;
    // std::cout << file4 << std::endl;
    // std::cout << std::endl;

    // // move constructor
    // File file6;
    // File file5(std::move(file6));       
    // std::cout << file5 << std::endl;
    // std::cout << std::endl;

    // move assignment
    // int array8[256];
    // File file7("ee.txt", "hello", array8);
    // file7 = std::move(file7);   // should skip
    // File file8 = std::move(file7);
    // std::cout << file8 << std::endl;

    // destructor (all objects created above should call their constructors due to being out of scope by the end)

    // folder getSize
    Folder folder1("folder1");
    File fileA("A.txt", "12345");
    File fileB("B.txt", "12345678");
    File fileC("C.txt", "123");
    folder1.addFile(fileA);
    folder1.addFile(fileB);
    folder1.addFile(fileC);
    // folder1.display();

    // std::cout << "folder is " << folder1.getSize() << " bytes" << std::endl;        // should be 16

    // addFile that already exists
    // File fileD("A.txt", "12345");
    // folder1.addFile(fileD);
    // folder1.display();

    // add empty file
    // File fileE;
    // File fileF(std::move(fileE));
    // std::cout << folder1.addFile(fileE) << std::endl;      // should be 0

    // removeFile
    // folder1.removeFile("C.txt");
    // folder1.display();

    // // move
    Folder folder2("folder2");
    // folder1.moveFileTo("B.txt", folder2);
    // folder1.display();
    // folder2.display();

    // // file not found 
    // folder1.moveFileTo("Z.txt", folder2);
    // folder1.display();

    // // move to self
    // folder1.moveFileTo("A.txt", folder1);
    // folder1.display();

    // copy
    folder1.display();
    folder2.display();
    if (folder1.copyFileTo("A.txt", folder2)) {
        std::cout << "success" << std::endl;
        folder1.display();
        folder2.display();
    }
    else {
        std::cout << "fail";
    }
}