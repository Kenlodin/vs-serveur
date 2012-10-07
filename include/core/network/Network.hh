/*
 * Network.hh
 *
 *  Created on: 17 avr. 2012
 *      Author: nagriar
 */

#ifndef NETWORK_HH_
# define NETWORK_HH_

//External include
#include <boost/bind.hpp>

//Internal include
# include <core/thread/Thread.hh>
# include <core/fwd.hh>
# include <core/log/Log.hh>
# include <core/network/Dispatcher.hh>

/*
 * Class which manager input connection and routing
 */
class Network : public tools::Thread
{
  public:
    /**
     *  Constructor
     *  @param control_port of the server
     *  @param data_port of the server
     */
    Network(std::list<unsigned short>& ports);

    /**
     *  Destructor
     */
    virtual ~Network();
  public:
    /**
     *  Run accepting and routing process
     */
    void run ();

    /**
     *  Add client in list if aceptation succeed
     */
    void handleAccept(Client* newClient, int index
        , const boost::system::error_code& error);

    /**
     *  Start accept on every socket of server
     */
    void startAccepts();

    /**
     *  Start accept on socket of server with this index
     */
    void startAccept(int index);
  private:
    // Variables of server
    std::list<unsigned short> serverPorts_;

    boost::asio::io_service ioService_;

    std::vector<boost::asio::ip::tcp::acceptor> acceptors_;
};

#endif /* NETWORK_HH_ */
