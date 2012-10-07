#include <core/network/Dispatcher.hh>
# include <core/thread/WorkList.hh>
# include <core/client/Client.hh>

Dispatcher::Dispatcher()
    : route_(
    {
        &Dispatcher::clientTracker,
        &Dispatcher::trackerClient,
        &Dispatcher::clientDiffusion,
        &Dispatcher::diffusionClient,
        &Dispatcher::diffusionDiffusion,
        &Dispatcher::clientNone,
        &Dispatcher::adminServer})
{

}

Dispatcher::~Dispatcher()
{

}

Dispatcher& Dispatcher::getInstance()
{
  static Dispatcher instance_;

  return instance_;
}

void Dispatcher::routing(Packet& packet, Client*& client)
{
  uint16_t opcode;
  unsigned int type;
  unsigned int code;

  packet >> opcode;
  code = EXTRACT_CODE(opcode);
  type = EXTRACT_TYPE(opcode);
  if (type < ConnexionType::LENGTH)
    (this->*route_[type])(code, packet, client);
  else
  {
    COUTDEBUG("Network : mauvais routing.");
    ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
  }
}

void Dispatcher::clientTracker(unsigned int route, Packet& packet,
    Client*& client)
{
  COUTDEBUG("Client*& --> Tracker");
  WorkList<Tracker>::getInstance().putWorks(&Tracker::routing, route, packet,
      client);
}

void Dispatcher::trackerClient(unsigned int route __attribute__((unused))
  , Packet& packet __attribute__((unused)), Client*& client)
{
  COUTDEBUG("Tracker --> Client");
  COUTDEBUG("Client*& : mauvais routing.");
  ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
  //return RETURN_VALUE_ERROR;
}

void Dispatcher::clientDiffusion(unsigned int route, Packet& packet,
    Client*& client)
{
  COUTDEBUG("Client*& --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing, route,
      packet, client);
}

void Dispatcher::diffusionClient(unsigned int route __attribute__((unused))
  , Packet& packet __attribute__((unused)), Client*& client)
{
  COUTDEBUG("Diffusion --> Client");
  COUTDEBUG("Client*& : mauvais routing.");
  ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
  //return RETURN_VALUE_ERROR;
}

void Dispatcher::diffusionDiffusion(unsigned int route, Packet& packet,
    Client*& client)
{
  COUTDEBUG("Diffusion --> Diffusion");
  WorkList<Diffusion>::getInstance().putWorks(&Diffusion::routing_internal,
      route, packet, client);
}

void Dispatcher::clientNone(unsigned int route, Packet& packet, Client*& client)
{
  ClientList::getInstance().addBadClient(client, RETURN_VALUE_ERROR);
}

void Dispatcher::adminServer(unsigned int route, Packet& packet
        , Client*& client)
{
  WorkList<AdminServer>::getInstance ().putWorks (&AdminServer::routing,
                                                  route, packet, client);
}

inline
void Dispatcher::readHeaderHandler(Packet& packet, Client* client
  , boost_socket* sock, const boost::system::error_code& error)
{
  if (error)
    return;
  int size = packet.GetData()[0];
  size = (size << 4) | packet.GetData()[1];
  size = (size << 4) | packet.GetData()[2];
  size = (size << 4) | packet.GetData()[3];
  sock->async_read_some(boost::asio::buffer(packet.GetData(), size)
    , boost::bind(&Dispatcher::readBodyHandler, this, packet, client, sock
      , boost::asio::placeholders::error));
}

inline
void Dispatcher::readBodyHandler(Packet& packet, Client* client, boost_socket* sock
  , const boost::system::error_code& error)
{
  if (error)
    return;
  routing(packet, client);
  Packet newPacket = Packet();
  sock->async_read_some(boost::asio::buffer(newPacket.GetData(), 4)
    , boost::bind(&Dispatcher::readHeaderHandler, this, newPacket, client, sock
      , boost::asio::placeholders::error));
  
}

void Dispatcher::launchAsyncRead(Client* client, boost_socket& sock)
{
  Packet packet = Packet();
  sock.async_read_some(boost::asio::buffer(packet.GetData(), 4)
    , boost::bind(&Dispatcher::readHeaderHandler, this, packet, client, &sock
      , boost::asio::placeholders::error));
}
