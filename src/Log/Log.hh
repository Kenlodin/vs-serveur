/* 
 * File:   Log.hh
 * Author: Aymeric
 *
 * Created on 18 avril 2012, 20:24
 */

#ifndef LOG_HH
#define	LOG_HH

#include <iostream>
#include <fstream>

# define DEBUG

# ifdef DEBUG
#  define COUTDEBUG(MSG) std::cout << MSG << std::endl
# else
#  define COUTDEBUG(MSG) void
# endif

/**
 * La classe log permet de mettre en place un systeme de log. C'est un singleton
 * qui ne nécessite pas d'être thread-safe puisqu'il doit être appellé pour être
 * initialisé
 * 
 * @param file
 */
class Log
{
  public:
    /**
     * Indique le fichier dans lequel les logs doivent être enregistrées. C'est
     * cette fonction qui ouvre le fichier.
     * @param file Le fichier
     */
    void setFile(std::string file);

    /**
     * Permet d'écrire le log. Le log est enregistré dans la forme suivante :
     * [$tag] $msg
     * Un retours à la ligne est automatiquement ajouté en fin de ligne.
     * @param tag Le tag associé au message
     * @param msg Le message
     */
    void write(std::string tag, std::string msg);

    /**
     * Permet de savoir si le système de log est actif.
     * @return bool
     */
    bool getIsActive();

  private:
    std::ofstream file_;
    bool isActive_;

  public:
    static Log& getInstance();

  private:
    Log()
    {
    }
    ~Log()
    {
    }
};

#endif	/* LOG_HH */

