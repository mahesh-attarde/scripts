import gdb
"""
This is command used to avoid "call object->dump()" for LLVM Classes.
E.g. Use "du MI_obj" which will call MI->dump() directly
TODO:
1. Add Reference call Obj.dump()
"""
class CallClassMethod(gdb.Command):
    """
    Call a dump function of a LLVM class in GDB.
    Usage: du object_expression ...
    """
    def __init__(self):
        super(CallClassMethod, self).__init__("du", gdb.COMMAND_USER)
    def marker(r, g, b, text):
        return f"\033[38;2;{r};{g};{b}m{text}\033[0m"
    def invoke(self, arg, from_tty):
        args = gdb.string_to_argv(arg)
        if len(args) < 1:
            raise gdb.GdbError("Usage: du object_expression ...")
        object_expression = args[0]
        function_name = "dump"
        try:
            object_instance = gdb.parse_and_eval(object_expression)
            function_object = object_instance[function_name]
            function_type = gdb.parse_and_eval(f"{object_instance.type}::{function_name}").type     
            converted_args = []
            print("[GDB-DUMP-START]")
            result = function_object.cast(function_type)(object_instance.address, *converted_args)
            print("[GDB-DUMP-END]")

        except gdb.GdbError as e:
            print(f"Extension Error: {e}")

CallClassMethod()
