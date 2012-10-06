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
# include <core/diffusion/Diffusion.hh>
# include <core/tracker/Tracker.hh>
# include <core/log/Log.hh>

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
     *  Read header of packet
     */
    void readHeaderHandler(Packet& paquet, Client* client, boost_socket* sock, const boost::system::error_code& error);


    /**
     *  Read body of packet
     */
    void readBodyHandler(Packet& paquet, Client* client, boost_socket* sock, const boost::system::error_code& error);

    /**
     *  Load async read
     */ 
    void launchAsyncRead(Client* client);

    /**
     *  Start accept on every socket of server
     */
    void startAccepts();

    /**
     *  Start accept on socket of server with this index
     */
    void startAccept(int index);
    /**
     *  Function which route packet
     *  @param packet received
     *  @param Client*& who send this packet
     */
    void routing(Packet& packet, Client*& client);
  private:
    // typedef of fonction handler
    typedef void (Network::*handler)(unsigned int route, Packet& packet
        , Client*& client);

    // Constant Array of handler
    const handler route_[ConnexionType::LENGTH];
  private:
    // Fonction handlers //
    /**
     *  Route a packet from Client*& to tracker
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void clientTracker(unsigned int route, Packet& packet
        , Client*& client);

    /**
     *  Route a packet from tracker to client
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void trackerClient(unsigned int route, Packet& packet
        , Client*& client);

    /**
     *  Route a packet from Client*& to diffusion
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void clientDiffusion(unsigned int route, Packet& packet
        , Client*& client);

    /**
     *  Route a packet from diffusion to client
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void diffusionClient(unsigned int route, Packet& packet
        , Client*& client);

    /**
     *  Route a packet from diffusion to diffusion
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void diffusionDiffusion(unsigned int route, Packet& packet
        , Client*& client);
    
    /**
     *  Route a packet from administrator to server
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void adminServer(unsigned int route, Packet& packet
        , Client*& client);
  private:
    // Variables of server
    std::list<unsigned short> serverPorts_;

    boost::asio::io_service ioService_;

    std::vector<boost::asio::ip::tcp::acceptor> acceptors_;
};

# include <core/network/Network.hxx>

#endif /* NETWORK_HH_ */
