from ctypes import *
c_object_p = POINTER(c_void_p)

class Int_error(Exception):
    def __init__(self):
        self.value = conf.lib.Int_error()
        conf.lib.Int_clear_error()

    def __str__(self):
        return self.value

class Int: 
   
  def __init__(self,  value=None, _p=None):
    if _p:
      self.ptr = _p
    else:
      self.ptr = c_object_p()
      rc = conf.lib.Int_Int_create(value, byref(self.ptr))
      if rc != 0:
        raise Int_error()
    
  def value(self):
    rv = c_int()
    rc = conf.lib.Int_value(self, byref(rv))
    if rc == 0:
      return rv.value
    raise Int_error() 
    
  def from_param(self):
    return self.ptr

  def __del__(self):
    conf.lib.Int_dispose(self)



methodList = [

  ("Int_error",
  [],
  c_char_p),

  ("Int_clear_error",
  [],
  None),

  ("Int_dispose",
  [Int],
  None), 

  ("Int_value",
  [Int, POINTER(c_int)],
  c_int)
]

# library loading and method registrations
# based on clang python bindings approach

def register_method(lib, item):
  func = getattr(lib, item[0])

  if len(item) >= 2:
    func.argtypes = item[1]

  if len(item) >= 3:
    func.restype = item[2]


class CachedProperty(object):

    def __init__(self, wrapped):
        self.wrapped = wrapped
        try:
            self.__doc__ = wrapped.__doc__
        except:
            pass

    def __get__(self, instance, instance_type=None):
        if instance is None:
            return self

        value = self.wrapped(instance)
        setattr(instance, self.wrapped.__name__, value)

        return value

class Config:
    library_path = None
    loaded = False

    @staticmethod
    def set_library_path(path):
        if Config.loaded:
            raise Exception("library path is already set.")
        Config.library_path = path

    @CachedProperty
    def lib(self):
        lib = self._get_library()
        map(lambda x:register_method(lib,x), methodList)
        Config.loaded = True
        return lib

    def _get_filename(self):
        import platform
        name = platform.system()

        if name == 'Darwin':
            file = 'libInt_c.dylib'
        elif name == 'Windows':
            file = 'Int_c.dll'
        else:
            file = 'libInt_c.so'

        if Config.library_path:
            file = Config.library_path + '/' + file

        return file

    def _get_library(self):
        try:
            library = cdll.LoadLibrary(self._get_filename())
        except OSError as e:
            msg = str(e) + ". To provide a path to Int dylib use Config.set_library_path()"
            raise Exception(msg)

        return library

conf = Config()


