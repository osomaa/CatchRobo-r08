uint8  id           # 関節/モータID
string state        # "goal" | "wait" | "timeout"
float32 error       # |pos - target|
builtin_interfaces/Time stamp
