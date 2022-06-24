package checksum

import "math/bits"

type CRCModel struct {
	Poly   uint8
	Init   uint8
	RefIn  bool
	RefOut bool
	XorOut uint8
	Name   string
}

func CRC8(data []byte, model CRCModel) uint8 {
	table := getTable(model)
	crcResult := model.Init
	crcResult = addBytes(data, model, crcResult, table)
	if model.RefOut {
		crcResult = bits.Reverse8(crcResult)
	}
	return crcResult ^ model.XorOut
}

func addBytes(data []byte, model CRCModel, crcResult uint8, table []uint8) uint8 {
	if model.RefIn {
		for _, d := range data {
			d = bits.Reverse8(d)
			crcResult = table[crcResult^d]
		}
		return crcResult
	}
	for _, d := range data {
		crcResult = table[crcResult^d]
	}
	return crcResult
}

func getTable(model CRCModel) []uint8 {
	table := make([]uint8, 256)
	for i := 0; i < 256; i++ {
		crc := uint8(i)
		for j := 0; j < 8; j++ {
			isSetBit := (crc & 0x80) != 0
			crc <<= 1
			if isSetBit {
				crc ^= model.Poly
			}
		}
		table[i] = crc
	}
	return table
}
