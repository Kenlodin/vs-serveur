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
