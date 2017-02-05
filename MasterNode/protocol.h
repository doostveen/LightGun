#ifndef PROTOCOL
#define PROTOCOL
#endif

struct deviceId
{
  byte teamId = 0;
  byte memberId = 0;
};

struct message
{
  //deviceId deviceId;
  int sequentialId = 0; 
  byte command = 0;
  byte payload = 0;
};

