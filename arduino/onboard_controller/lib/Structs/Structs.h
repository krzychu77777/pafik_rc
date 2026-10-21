#ifndef PAFIK_LOGBUFF
#define PAFIK_LOGBUFF

struct logBuff {
public:
    static constexpr uint8_t size = 10;
    BackLog log_queue[size];
    uint8_t head = 0;
    uint8_t tail = 0;
    uint16_t dropped_logs = 0;

    bool empty() {
        return head==tail;
    }

    void push(BackLog log) {
      if (tail == head-1 || (tail==size-1 && head==0)) {
        // logger.warning(log_queue_overflow);
        dropped_logs++;
      }
      else {
        log_queue[tail] = log;
        if(tail<size-1) tail++;
        else tail=0;
      }
    }

    bool pop(BackLog& output) {
      if(empty()) {
        return false;
      }
      else {
        output = log_queue[head];
        if(head<size-1) head++;
        else head=0;
        return true;
      }
    }
};

class PacketManager {


};

#endif