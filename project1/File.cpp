#include "File.hpp"
      
std::string File::getName() const {
   return filename_;
}

std::string File::getContents() const {
   return contents_;
}

void File::setContents(const std::string& new_contents) {
   contents_ = new_contents;
}

int* File::getIcon() const {
   return icon_;
}

void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a; 
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================
/**
 * @brief Constructs a new File object.
 * 
 * @param filename A const reference to a string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
 *    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
 *    - If no extension is provided (e.g. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
 *    - Default value of "NewFile.txt" if none provided or if filename is empty 
 * @param contents A string representing the contents of the file. Default to empty string if none provided.
 * @param icon A pointer to a [dynamically allocated] integer array with length ICON_DIM. Default to nullptr if none provided.
 * @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
 * @note You'll notice we provide a default value for the first possible argument (filename)
 *       Yes, this means we can define override the default constructor and define a parameterized one simultaneously.
 */
File::File(const std::string& filename, const std::string& contents, int* icon) {
    // std::cout<< "calling basic constructor on " << this << std::endl;
    // check if filename is valid
    int numberOfPeriods = 0;
    for (int i = 0; i < filename.length(); i++) {
        // check if this char is a period
        if (filename[i] == '.') {
            numberOfPeriods++;
        }
        // if not period, check if alnum
        else if (!isalnum(filename[i])) {
            throw InvalidFormatException();
        }
        // if too many periods, throw exception
        if (numberOfPeriods > 1) {
            throw InvalidFormatException();
        }
    }
    // if the filename is empty
    if (filename == "") {
        filename_ = "NewFile.txt";
    }
    // if there is no extension after the period
    else if (filename[filename.length() - 1] == '.') {
        filename_ = filename + "txt";
    }
    // if there is no period
    else if (numberOfPeriods == 0) {
        filename_ = filename + ".txt";
    }
    // if the filename is valid
    else {
        filename_ = filename;
    }
    contents_ = contents;
    icon_ = icon;           // icon has dynamic memory

}

/**
 * @brief Calculates and returns the size of the File Object (IN BYTES), using .size()
 * @return size_t The number of bytes the File's contents consumes
 * @note Consider this: how does this relate to the string's length? Why is that the case?
 */
size_t File::getSize() const {
    // icon_ should be 4 * ICON_DIM bytes if it's not null ptr
    // int iconSize = (icon_ == nullptr) ? sizeof(icon_) : sizeof(icon_) + sizeof(int) * ICON_DIM;
    return contents_.size();
}

/**
 * @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
 * @param rhs A const reference to the file to be copied from
 */
File::File(const File& rhs) {
    // std::cout<< "calling copy constructor on " << this << " to copy " << std::addressof(rhs) << std::endl;
    filename_ = rhs.getName();
    contents_ = rhs.getContents();

    // if rhs.getIcon() is nullptr, set to nullptr
    int* shallow = rhs.getIcon();
    if (shallow == nullptr) {
        // can't use setIcon here. setIcon is only reliable if icon_ has been initialized already
        // if icon_ is not set to nullptr, it might attempt to delete[] memory that doesn't exist
        icon_ = nullptr;        
    }
    // else, do a deep copy
    else {
        // create a new array with dynamic memory
        icon_ = new int[ICON_DIM];
        for(int i = 0; i < ICON_DIM; i++) {
            icon_[i] = shallow[i];
        }
    }
}

/**
 * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File.
 * 
 * @param rhs A const reference to the File object to be copied
 * @return A reference to the new File copy
 * @note If copy assignment operator is invoked upon itself, do nothing.
 */
File& File::operator=(const File& rhs) {
    // If copy assignment operator is invoked upon itself, do nothing.
    if (this == &rhs) {
        return *this;
    }

    // std::cout<< "calling copy assignment on " << this << " to copy " << std::addressof(rhs) << std::endl;

    filename_ = rhs.getName();
    contents_ = rhs.getContents();

    int* shallow = rhs.getIcon();
    // if rhs.getIcon() is nullptr, set to nullptr
    if (shallow == nullptr) {
        // use setIcon to take care of deleting the existing icon
        setIcon(nullptr);
    }
    // if icon_ is currently nullptr, we must create a new array
    else if (icon_ == nullptr) {
        int* deep = new int[ICON_DIM];
        for(int i = 0; i < ICON_DIM; i++) {
            deep[i] = shallow[i];
        }
        // use setIcon to take care of deleting the existing icon
        setIcon(deep);
    }
    // if icon_ is not nullptr, we can just override existing values
    else if (icon_ != nullptr) {
        for(int i = 0; i < ICON_DIM; i++) {
            icon_[i] = shallow[i];
        }
    }

    return *this;
}

/**
 * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
 * @param rhs The File whose data is moved
 * @post The rhs File object is left in a valid, but ready to be deleted state:
 *    - All string members are themselves moved.
 *    - ALl pointers are set to nullptr
 */
File::File(File&& rhs) {
    // std::cout<< "calling move constructor on " << this << " to move " << std::addressof(rhs) << std::endl;
    filename_ = std::move(rhs.filename_);
    contents_ = std::move(rhs.contents_);
    icon_ = std::move(rhs.icon_);
    
    rhs.icon_ = nullptr;
}

/**
 * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
 * 
 * @param rhs The File whose data is moved
 * @return A reference to the object which the data was moved into
 * @post The rhs File object is left in a valid, but ready to be deleted state:
 *    - All string members are moved.
 *    - ALl pointers are set to nullptr
 * @note If move assignment operator is invoked upon itself, do nothing.
 */
File& File::operator=(File&& rhs) {
    if (this == &rhs) {
        return *this;
    }

    // std::cout<< "calling move assignment on " << this << " to move " << std::addressof(rhs) << std::endl;
    filename_ = std::move(rhs.filename_);
    contents_ = std::move(rhs.contents_);
    icon_ = std::move(rhs.icon_);

    rhs.icon_ = nullptr;

    return *this;
}

/**
 * @brief (DESTRUCTOR) Routine for object deletion
 * @post All dynamically allocated memory is released
 */
File::~File() {
    // std::cout<< "calling destructor on " << this << std::endl;
    if (icon_ != nullptr) {
        delete[] icon_;
    }
}
