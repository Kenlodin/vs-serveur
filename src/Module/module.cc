#include <core/module/module.hh>

Module::Module(std::string filename)
{
  infos_["filename"] = filename;
  loaded_ = false;
  load_infos();
  load_module();
  module_ = NULL;
}

std::string
Module::get_info(std::string name)
{
  if (infos_.find(name) != infos_.end())
    return "";
  return infos_[name];
}

void
Module::print()
{
  std::cout << std::endl;
  for (map_infos::iterator it = infos_.begin(); it != infos_.end(); it++)
    std::cout << it->first << " => " << it->second << std::endl;
}

void
Module::load_infos()
{
  int fd = 0;
  Elf32_Ehdr ehdr;

  fd = open(infos_["filename"].c_str(), O_RDONLY);
  if (fd == -1)
  {
    std::cerr << "file not found: " << infos_["filename"] << std::endl;
    return;
  }
  read(fd, &ehdr, sizeof(ehdr));
  lseek(fd, 0, SEEK_SET);
  if (ehdr.e_ident[EI_CLASS] == ELFCLASS64)
    load_infos_64(fd);
  else
    load_infos_32(fd);
  close(fd);
}

void
Module::load_infos_32(int fd)
{
  void        *buffer = NULL;
  int         offset = 0, size = 0, count = 2;
  char        *temp;

  buffer = calloc(1, 1024);
  read(fd, buffer, sizeof (Elf32_Ehdr));

  offset = ((Elf32_Ehdr*)buffer)->e_shoff;
  lseek(fd, (((Elf32_Ehdr*)buffer)->e_shstrndx * sizeof (Elf32_Shdr)) + offset, SEEK_SET);
  read(fd, buffer, sizeof (Elf32_Shdr));

  lseek(fd, ((Elf32_Shdr*)buffer)->sh_offset, SEEK_SET);
  size = ((Elf32_Shdr*)buffer)->sh_size;
  read(fd, buffer, size);
  temp = (char*)buffer;

  while (--size && strcmp(++temp, ".modinfo"))
  {
    count++;
    while (*temp && size--)
    {
      temp++;
    }
  }
  if (!size)
  {
    std::cerr << "module non conforme" << std::endl;
    return;
  }

  lseek(fd, offset + (count * sizeof (Elf32_Shdr)), SEEK_SET);
  read(fd, buffer, sizeof (Elf32_Shdr));
  lseek(fd, ((Elf32_Shdr*)buffer)->sh_offset, SEEK_SET);
  read(fd, buffer, 1024);
  get_info_in_char((char*)buffer);
}

void
Module::load_infos_64(int fd)
{
  void        *buffer = NULL;
  int         offset = 0, size = 0, count = 2;
  char        *temp;

  buffer = calloc(1, 1024);
  read(fd, buffer, sizeof (Elf64_Ehdr));

  offset = ((Elf64_Ehdr*)buffer)->e_shoff;
  lseek(fd, (((Elf64_Ehdr*)buffer)->e_shstrndx * sizeof (Elf64_Shdr)) + offset, SEEK_SET);
  read(fd, buffer, sizeof (Elf64_Shdr));

  lseek(fd, ((Elf64_Shdr*)buffer)->sh_offset, SEEK_SET);
  size = ((Elf64_Shdr*)buffer)->sh_size;
  read(fd, buffer, size);
  temp = (char*)buffer;

  while (--size && strcmp(++temp, ".modinfo"))
  {
    count++;
    while (*temp && size--)
    {
      temp++;
    }
  }
  if (!size)
  {
    std::cerr << "module non conforme" << std::endl;
    return;
  }

  lseek(fd, offset + (count * sizeof (Elf64_Shdr)), SEEK_SET);
  read(fd, buffer, sizeof (Elf64_Shdr));
  lseek(fd, ((Elf64_Shdr*)buffer)->sh_offset, SEEK_SET);
  read(fd, buffer, 1024);
  get_info_in_char((char*)buffer);
}

void
Module::load_infos_128(int fd __attribute__((unused)))
{
  std::cout << "You love it" << std::endl;
}

void
Module::load_module()
{
  fun_maker fun = NULL;

  module_ptr_ = dlopen(infos_["filename"].c_str(), RTLD_LAZY | RTLD_GLOBAL);
  if (module_ptr_ == NULL)
    std::cerr << "error in load module named " << infos_["filename"] << std::endl;
  
  fun = (fun_maker)dlsym(module_ptr_, "makeModule");
  if (fun)
    module_ = fun();
}

void
Module::get_info_in_char(char *str)
{
  std::string       name;
  std::string       info;
  char              *base;

  while (*str)
  {
    base = str;
    while (*str != '=')
      str++;
    *str = 0;
    str++;
    name = base;
    info = str;
    infos_[name] = info;
    while (*str)
      str++;
    str++;
  }
}
