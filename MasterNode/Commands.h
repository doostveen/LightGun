#ifndef COMMANDS
#define COMMANDS
#endif

// defines binary commands and command structure
#define CMD_CONTROLLER_FIND 1             // Connect to game controller if any. Payload contains requested teamId.
#define CMD_CONTROLLER_CONNECT 2          // Connects to gamecontroller. Payload returns deviceId.
#define CMD_HIT 8                         // Hit by other device. Payload contains the device Id of the firing device.
#define CMD_GAME_START 16                 // Starts the game. Payload contains the game duration.
#define CMD_GAME_END  17                  // Game ends now. Freezes all guns.
#define CMD_GAME_REMAINING_END 18         // Remaining gameduration. Payload contains the duration left in seconds.
#define CMD_GAME_REMAING_START 19         // Remaining time before game starts. Payload contains time before start.
#define CMD_AMMO_ADD 32                   // Adds the specified number of ammo. Payload contains target device and number of ammo to add.
#define CMD_ACK  255                      // acknowledge the specified command. Payload contains the deviceId and sequentialId
