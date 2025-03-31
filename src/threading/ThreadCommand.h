//
// Created by Brandon on 3/30/25.
//

#ifndef RGBLIB_COMMANDTASK_H
#define RGBLIB_COMMANDTASK_H


namespace rgb {

class ThreadCommand {
public:
  virtual void execute() = 0;
  virtual ~ThreadCommand() = default;
};

}


#endif //RGBLIB_COMMANDTASK_H
