import ctypes
from ctypes.util import find_library


class Rect(ctypes.Structure):
    _fields_ = [('l', ctypes.c_int),
                ('t', ctypes.c_int),
                ('w', ctypes.c_int),
                ('h', ctypes.c_int)]


lib_ffld2 = ctypes.cdll.LoadLibrary(find_library("ffld2"))
# detect function wrapper
detect = lib_ffld2.detect
detect.argtypes = [ctypes.POINTER(Rect), ctypes.POINTER(ctypes.c_ubyte), ctypes.c_int, ctypes.c_int, ctypes.c_int,
                   ctypes.c_int, ctypes.c_int, ctypes.c_double, ctypes.c_bool, ctypes.c_double, ctypes.c_double]
detect.restype = ctypes.c_bool


def face_detector(img, padding=6, interval=5, threshold=0.5, cache_wisdom=True, overlap=0.3, adaptive_min_size=0.1):
    rect = Rect()
    image_data = img.ctypes.data_as(ctypes.POINTER(ctypes.c_ubyte))
    height, width, channels = img.shape
    res = detect(rect, image_data, width, height, channels,
                 padding, interval, threshold, cache_wisdom, overlap, adaptive_min_size)
    return res, rect
