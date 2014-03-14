# encoding: utf-8

#  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
#  Licensed under the terms of the WTFPL.
#
#  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
#  0. You just DO WHAT THE FUCK YOU WANT TO.

# Note, the other part of this code is not WTFPL! Only the printers, not the procedure to import the printers!
# This is because it is cloned from a different project from a different author.

from SpringbokGDB.printerImport import *
from SpringbokGDB.printerImport import _register_printer

if sys.version_info[0] == 3:
    Iterator = object
else:
    class Iterator(object):
        def next(self):
            return type(self).__next__(self)

@_register_printer
class SpringbokList:
	"Pretty Printer for Springbok Lists"
	printer_name = 'Springbok.Containers.List'
	version = '1.00'
	type_name_re = '^List<(.*)>$'

	class _iterator(Iterator):
		def __init__(self, val):
			self.val = val
			self.count = 0

		def __iter__(self):
			return self

		def __next__(self):
			if self.count >= self.val['MemoryLength']:
				raise StopIteration
			count = self.count

			self.count = self.count + 1
			return ('[%d]%s' % (count, "*" if count > self.val['UsedLength'] else ""), self.val['Memory'][count])

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return 'List(%d/%d)' % (self.value['UsedLength'], self.value['MemoryLength'])
	
	def children(self):
			return self._iterator(self.value)
		
	def display_hint(self):
			return 'array'
		
@_register_printer
class SpringbokMemorySubrange:
	"Pretty Printer for MemorySubrange"
	printer_name = 'Springbok.Containers.MemorySubrange'
	version = '1.00'
	type_name_re = '^MemorySubrange<(.*)>$'

	class _iterator(Iterator):
		def __init__(self, val):
			self.val = val
			self.count = 0

		def __iter__(self):
			return self

		def __next__(self):
			if self.count >= (self.val['mEnd'] - self.val['mBegin']):
				raise StopIteration
			count = self.count

			self.count = self.count + 1
			return ('[%d]' % (count), self.val['mBegin'][count])

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return '%s(%d elements from %s)' % (self.typename, self.value['mEnd'] - self.value['mBegin'], self.value['mBegin'])
	
	def children(self):
			return self._iterator(self.value)
		
	def display_hint(self):
			return 'array'
		
@_register_printer
class SpringbokContainerSubrange:
	"Pretty Printer for ContainerSubrange"
	printer_name = 'Springbok.Containers.ContainerSubrange'
	version = '1.00'
	type_name_re = '^ContainerSubrange<(.*)>$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return 'ContainerSubrange(%s:%s[%d -> %d]; length %d)' % (self.value['mContainer'], self.value['mContainer'].dereference(), self.value['mBegin'], self.value['mEnd'], self.value['mEnd'] - self.value['mBegin'])
		
@_register_printer
class SpringbokVec2:
	"Pretty Printer for Springbok 2D Vectors"
	printer_name = 'Springbok.Geometry.Vec2'
	version = '1.00'
	type_name_re = '^Vec2<(.*)>$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return 'Vec2(%s : %s)' % (self.value['X'], self.value['Y'])
	
	
@_register_printer
class SpringbokVec3:
	"Pretty Printer for Springbok 3D Vectors"
	printer_name = 'Springbok.Geometry.Vec3'
	version = '1.00'
	type_name_re = '^(Vec3<(.*)>)|(Color)$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return 'Vec3(%s : %s : %s)' % (self.value['X'], self.value['Y'], self.value['Z'])
	
@_register_printer
class SpringbokRange:
	"Pretty Printer for Springbok 1D Ranges"
	printer_name = 'Springbok.Math.Range'
	version = '1.00'
	type_name_re = '^Range<(.*)>$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return 'Range(%s -> %s)' % (self.value['MinVal'], self.value['MaxVal'])
	
@_register_printer
class SpringbokAngle:
	"Pretty Printer for Springbok Angles"
	printer_name = 'Springbok.Geometry.Angle'
	version = '1.00'
	type_name_re = '^Angle$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return '%d°' % (float(self.value['Data']) / 6.2831853 * 360)
	
@_register_printer
class SpringbokBoundingRect:
	"Pretty Printer for Springbok Angles"
	printer_name = 'Springbok.Geometry.BoundingRect'
	version = '1.00'
	type_name_re = '^BoundingRect$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		return 'BoundingRect<%d * %d @ %d : %d>' % (self.value['Size']['X'], self.value['Size']['Y'], self.value['Position']['X'], self.value['Position']['Y'])
	
@_register_printer
class SpringbokImage:
	"Pretty Printer for Springbok Images"
	printer_name = 'Springbok.Graphics.Image'
	version = '1.00'
	type_name_re = '^Image$'

	def __init__(self, value):
		self.typename = value.type_name
		self.value = value

	def to_string(self):
		# wth, why isn't this working
		#if self.value['mTexture'] == 0x0:
		#	return 'Image(unloaded %s)' % (self.value['mPath'])
		return 'Image<%d * %d @ %d : %d in %s>' % (self.value['mSize']['X'], self.value['mSize']['Y'], self.value['mOffset']['X'], self.value['mOffset']['Y'], self.value['mPath'])