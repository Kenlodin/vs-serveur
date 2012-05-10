CREATE or REPLACE FUNCTION set_handlings (INTEGER, INTEGER, INTEGER, INTEGER, TEXT)
RETURNS void
AS
$$
  DECLARE
    nbpacket INTEGER := $1;
    time INTEGER := $2;
    coeff INTEGER := $3;
    file INTEGER := $4;
    current_packet INTEGER := 0;
    pstart INTEGER := 0;
    pend INTEGER := 0;
  BEGIN
    WHILE nbpacket > current_packet LOOP
      time := time + coeff;
      pstart := current_packet;
      pend := current_packet + 200;
      IF nbpacket - current_packet < 200 THEN
        pend := nbpacket;
      END IF;
      INSERT INTO client_handlings (file_id, date, packet_begin, packet_end, client_token) VALUES (file, time, pstart, pend, $5);
      current_packet := current_packet + 201;
    END LOOP;
  END ;
$$
LANGUAGE 'plpgsql';
