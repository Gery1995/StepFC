﻿#pragma once
// License: MIT  http://opensource.org/licenses/MIT
// Author: dustpg   mailto:dustpg@gmail.com
#include <stdint.h>

/// <summary>
/// PPU用标志 - $2000 - CTRL
/// </summary>
enum sfc_ppu_flag_2000 {
    SFC_PPU2000_NMIGen  = 0x80, // [0x2000]VBlank期间是否产生NMI
    SFC_PPU2000_Sp8x16  = 0x20, // [0x2000]精灵为8x16(1), 还是8x8(0)
    SFC_PPU2000_BgTabl  = 0x10, // [0x2000]背景调色板表地址$1000(1), $0000(0)
    SFC_PPU2000_SpTabl  = 0x08, // [0x2000]精灵调色板表地址$1000(1), $0000(0), 8x16模式下被忽略
    SFC_PPU2000_VINC32  = 0x04, // [0x2000]VRAM读写增加值32(1), 1(0)
};

/// <summary>
/// PPU用标志 - $2001 - MASK
/// </summary>
enum sfc_ppu_flag_2001 {
    SFC_PPU2001_Grey    = 0x01, // 灰阶使能
    SFC_PPU2001_BackL8  = 0x02, // 显示最左边的8像素背景
    SFC_PPU2001_SpriteL8= 0x04, // 显示最左边的8像素精灵
    SFC_PPU2001_Back    = 0x08, // 背景显示使能
    SFC_PPU2001_Sprite  = 0x10, // 精灵显示使能

    SFC_PPU2001_NTSCEmR = 0x20, // NTSC 强调红色
    SFC_PPU2001_NTSCEmG = 0x40, // NTSC 强调绿色
    SFC_PPU2001_NTSCEmB = 0x80, // NTSC 强调蓝色

    SFC_PPU2001_PALEmG  = 0x20, // PAL 强调绿色
    SFC_PPU2001_PALEmR  = 0x40, // PAL 强调红色
    SFC_PPU2001_PALEmB  = 0x80, // PAL 强调蓝色
};


/// <summary>
/// PPU用标志 - $2002 - STATUS
/// </summary>
enum sfc_ppu_flag_2002 {
    SFC_PPU2002_VBlank = 0x80, // [0x2002]垂直空白间隙标志
    SFC_PPU2002_Sp0Hit = 0x40, // [0x2002]零号精灵命中标志
    SFC_PPU2002_SpOver = 0x20, // [0x2002]精灵溢出标志
};


/// <summary>
/// PPU用标志 - 精灵属性
/// </summary>
enum sfc_ppu_flag_sprite_attr {
    SFC_SPATTR_FlipV   = 0x80, // 垂直翻转
    SFC_SPATTR_FlipH   = 0x40, // 水平翻转
    SFC_SPATTR_Priority= 0x20, // 优先位
};

/// <summary>
/// 
/// </summary>
typedef struct {
    // 内存地址库
    uint8_t*        banks[0x4000 / 0x0400];
    // 名称表选择(PPUCTRL低2位, 以及渲染中VRAM指针AB位)
    uint8_t         nametable_select;
    // 当前允许使用的垂直滚动偏移
    uint8_t         now_scrolly;
    // VRAM 地址
    uint16_t        vramaddr;
    // 寄存器 PPUCTRL      @$2000
    uint8_t         ctrl;
    // 寄存器 PPUMASK      @$2001
    uint8_t         mask;
    // 寄存器 PPUSTATUS    @$2002
    uint8_t         status;
    // 寄存器 OAMADDR      @$2003
    uint8_t         oamaddr;
    // 滚动偏移
    uint8_t         scroll[2];
    // 滚动偏移双写位置记录
    uint8_t         writex2;
    // 显存读取缓冲值
    uint8_t         pseudo;
    // 精灵调色板索引
    uint8_t         spindexes[0x20];
    // 精灵数据: 256B - 以32位对齐
    union {
        // 以32位对齐
        uint32_t    aligned_buffer[0x100 / 4];
        // 精灵数据: 256B
        uint8_t     sprites[0x100];
    };
} sfc_ppu_t;


// read ppu register via cpu address space
uint8_t sfc_read_ppu_register_via_cpu(uint16_t, sfc_ppu_t*);
// write ppu register via cpu address space
void sfc_write_ppu_register_via_cpu(uint16_t, uint8_t, sfc_ppu_t*);

