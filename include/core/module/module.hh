#ifndef MODULE_HH_
# define MODULE_HH_

// Cpp Includes
# include <iostream>
# include <map>
# include <string>
# include <sstream>

// Elf Includes
# include <elf.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

// Librairie Includes
# include <dlfcn.h>


# define SECTION_INFO_STR ".modinfo"

# define __STRINGIFY(STR)  #STR
# define __MODCAT(A, B)    __module_ ## A ## B

# define __MODULE_INFO(TAG, INFOS)                                  \
  static const char __MODCAT(TAG, __LINE__)[]                       \
    __attribute__((section(SECTION_INFO_STR), unused, aligned(1)))  \
    = __STRINGIFY(TAG) "=" INFOS

# define MODULE_AUTHORS(AUT)  __MODULE_INFO(authors, AUT)
# define MODULE_VERSION(VER)  __MODULE_INFO(version, VER)
# define MODULE_DESC(DESC)    __MODULE_INFO(desc, DESC)
# define MODULE_INIT(INIT)    __MODULE_INFO(init_fun, INIT)
# define MODULE_EXIT(EXIT)    __MODULE_INFO(exit_fun, EXIT)


/*
 * Type to describ infos conteneur
 */
typedef std::map<std::string, std::string> map_infos;

class Module
{
  public:
    /*
     * Load and get all infos on module
     * @param filename path to the module
     */
    Module(std::string filename);

    /*
     * Getter to get information to the module
     * @param name name of the information
     * @return the information needed
     */
    std::string get_info(std::string name);

    /*
     * Dump all information
     */
    void print();

    /*
     * TODO make deconstrutor
     */

  private:

    /*
     * Load information of the module
     */
    void load_infos();

    /*
     * Elf reader to 32/64/128 bit
     */
    void load_infos_32(int);
    void load_infos_64(int);
    void load_infos_128(int);
    
    /*
     * Load the module like librairie
     */
    void load_module();

    /*
     * Get information on a string
     */
    void get_info_in_char(char*);

  private:

    void                  *module_ptr_;
    map_infos             infos_;
    bool                  loaded_;

};

#endif /* !MODULE_HH_ */
