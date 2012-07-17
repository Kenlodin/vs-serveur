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

typedef std::map<std::string, std::string> map_infos;

class Module
{
  public:

    Module(std::string filename);
    std::string get_info(std::string name);
    void print();

  private:

    void load_infos();
    void load_infos_32(int);
    void load_infos_64(int);
    void load_infos_128(int);
    void load_module();
    void get_info_in_char(char*);

  private:

    void                  *module_ptr_;
    map_infos             infos_;
    bool                  loaded_;

};

#endif /* !MODULE_HH_ */
