/* 
 * File:   Config.hh
 * Author: Aymeric
 *
 * Created on 19 avril 2012, 16:41
 */

#ifndef CONFIG_HH
#define	CONFIG_HH

#include <map>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <tinyxml.h>
#include <core/tools/Tools.hh>
#include <core/sqlManager/SqlManager.hh>

class Config
{
 public:
   /**
    * Singleton accessor
    * @return 
    */
  static Config& getInstance ();
  
  /**
   * Load all the configuration
   * @param file
   */
  void load (std::string file);
  
  /**
  * Load the configuration file (config.xml)
  */
  void loadConfig ();
  
  /**
   * Insert in the database the file that the server have
   */
  void loadFiles ();

  /**
   * Print configuration
   */
  void print ();
  
  /**
   * Do nothing
   * @return 
   */
  bool check ();
  
  /**
   * Add a configuration
   * @param key
   * @param value
   */
  void add (std::string key, int value);
  
  /**
   * Add a configuration
   * @param key
   * @param value
   */
  void add (std::string key, std::string value);
  
  /**
   * Return the integer associated with the configuration key
   * @param key
   * @return 
   */
  int getInt (std::string key);
    /**
   * Return the integer associated with the configuration key
   * @param key
   * @return 
   */
  std::string getString (std::string key);
  /**
   * Set isOnline information
   * @param isOnline_
   */
  void setIsOnline(bool isOnline_);
  
  /**
   * Get isOnline information
   * @return 
   */
  bool isOnline() const;

 private:
  std::map<std::string, std::string> config_;
  TiXmlDocument c_;
  boost::mutex mutex_;
  bool isOnline_;
  Config () { isOnline_ = true; };
} ;

#endif	/* CONFIG_HH */

