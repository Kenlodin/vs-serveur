#ifndef DISPATCHER_HH
#define DISPATCHER_HH

# include <core/adminServer/AdminServer.hh>
# include <core/tracker/Tracker.hh>
# include <core/diffusion/Diffusion.hh>
# include <core/thread/Thread.hh>
# include <core/fwd.hh>
# include <core/log/Log.hh>

class Dispatcher
{
  public:
    Dispatcher();
    ~Dispatcher();
  public:
    // typedef of fonction handler
    typedef void (Dispatcher::*handler)(unsigned int route, Packet& packet
        , Client*& client);

    // Constant Array of handler
    const handler route_[ConnexionType::LENGTH];

    static Dispatcher& getInstance();

    /**
     *  Function which route packet
     *  @param packet received
     *  @param Client*& who send this packet
     */
    void routing(Packet& packet, Client*& client);
    

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
    void launchAsyncRead(Client* client, boost_socket& sock);
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
    

    void clientNone(unsigned int route, Packet& packet
        , Client*& client);
    
    /**
     *  Route a packet from administrator to server
     *  @param route second part of opcode
     *  @param packet received without opcode
     *  @param Client*& who send this message
     */
    void adminServer(unsigned int route, Packet& packet
        , Client*& client);
};

#endif /* DISPATCHER_HH */
