//==== FUN_001143a8 @ 001143a8 size=10826

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 FUN_001143a8(void)

{
  undefined3 uVar1;
  double dVar2;
  double dVar3;
  uint *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  undefined uVar18;
  undefined uVar19;
  undefined uVar20;
  undefined uVar21;
  undefined uVar22;
  undefined uVar23;
  undefined uVar24;
  undefined uVar25;
  undefined uVar26;
  undefined uVar27;
  undefined uVar28;
  char *pcVar29;
  byte *pbVar30;
  int iVar31;
  size_t sVar32;
  undefined4 *puVar33;
  ulong uVar34;
  undefined *puVar35;
  int iVar36;
  uint uVar37;
  int iVar38;
  byte *pbVar39;
  uint *__src;
  undefined1 *puVar40;
  int extraout_r1;
  int extraout_r1_00;
  byte bVar41;
  uint uVar42;
  undefined4 *puVar43;
  uint uVar44;
  int *piVar45;
  byte bVar46;
  int iVar47;
  undefined *puVar48;
  int iVar49;
  double *pdVar50;
  int *piVar51;
  double *pdVar52;
  double *pdVar53;
  uint uVar54;
  char *pcVar55;
  uint uVar56;
  int iVar57;
  undefined8 *puVar58;
  uint uVar59;
  int *piVar60;
  double *pdVar61;
  double *pdVar62;
  double *pdVar63;
  double *pdVar64;
  double *pdVar65;
  bool bVar66;
  double dVar67;
  double dVar68;
  double dVar69;
  double dVar70;
  float fVar73;
  double dVar71;
  double dVar72;
  double dVar74;
  float fVar75;
  float fVar76;
  undefined8 uVar77;
  undefined1 *local_57c;
  double *local_570;
  int local_56c;
  double *local_558;
  int local_554;
  double *local_54c;
  double *local_548;
  undefined4 local_530;
  undefined2 local_52c;
  uint local_528;
  undefined4 uStack_524;
  uint local_520;
  uint uStack_51c;
  undefined4 local_514;
  undefined4 local_510;
  undefined4 *local_50c;
  undefined4 local_508;
  undefined4 uStack_504;
  byte local_500;
  byte local_4ff;
  byte local_4fe;
  byte local_4fd;
  byte local_4fc;
  byte local_4fb;
  byte local_4fa;
  byte local_4f9;
  undefined local_4f8;
  undefined local_4f7;
  undefined local_4f6;
  undefined local_4f5;
  undefined local_4f4;
  undefined local_4f3;
  undefined local_4f2;
  undefined local_4f1;
  undefined local_4f0;
  undefined local_4ef;
  undefined local_4ee;
  undefined local_4ed;
  undefined local_4ec;
  undefined local_4eb;
  undefined local_4ea;
  undefined local_4e9;
  byte local_4e8;
  byte local_4e7;
  byte local_4e6;
  byte local_4e5;
  byte local_4e4;
  byte local_4e3;
  byte local_4e2;
  byte local_4e1;
  undefined4 local_4e0;
  undefined4 local_4dc;
  undefined2 local_4d8;
  undefined local_4d6;
  undefined local_4d5;
  undefined local_4d4;
  undefined local_4d3;
  undefined local_4d2;
  undefined local_4d1;
  undefined local_4d0;
  undefined local_4cf;
  undefined local_4ce;
  undefined local_4cd;
  undefined local_4cc;
  undefined local_4cb;
  undefined local_4ca;
  undefined local_4c9;
  undefined local_4c8;
  undefined local_4c7;
  undefined local_4c6;
  undefined local_4c5;
  undefined local_4c4;
  undefined local_4c3;
  undefined local_4c2;
  byte local_4c1;
  byte local_4c0 [72];
  undefined4 local_478;
  undefined4 local_474;
  char local_470;
  char local_46f;
  byte local_46e;
  byte local_46d;
  byte local_46c;
  byte local_46b;
  byte bStack_46a;
  byte bStack_469;
  byte bStack_468;
  byte bStack_467;
  byte local_466;
  byte local_465;
  byte local_464;
  
  __gnu_mcount_nc();
  uVar77 = __gnu_mcount_nc();
  iVar38 = (int)((ulonglong)uVar77 >> 0x20);
  local_528 = *(uint *)(iVar38 + 0x18b);
  uStack_524 = *(undefined4 *)(iVar38 + 399);
  pcVar29 = (char *)(DAT_00192828 + (int)uVar77 * 0x80);
  if (DAT_001923d8 != (undefined1 *)0x0) {
    FUN_0001a3e8(6,
                 "scanhash_kaspa_fpga(): thr_id=%d, jobid=%s, target=%llX, prefix=%02X%02X head=%.80s\n"
                 ,(int)uVar77,*(undefined4 *)(iVar38 + 0x108),local_528,uStack_524,
                 *(undefined *)(iVar38 + 0x189),*(undefined *)(iVar38 + 0x18a),iVar38 + 300);
  }
  memset(local_4c0,0,0x50);
  pbVar30 = &local_4c1;
  pbVar39 = (byte *)(iVar38 + 0x12d);
  local_50c = DAT_00117b74;
  local_514 = 0;
  local_510 = 0;
  local_508 = 0;
  uStack_504 = 0;
  do {
    while( true ) {
      bVar46 = pbVar39[-1];
      if ((byte)(bVar46 - 0x30) < 10) break;
      uVar54 = (uint)*pbVar39;
      uVar42 = bVar46 - 0x61;
      if (uVar42 < 6) {
        iVar47 = bVar46 - 0x57;
      }
      else {
        iVar47 = 0;
      }
      if (uVar42 < 6) {
        iVar47 = (iVar47 << 0x1c) >> 0x1c;
      }
      bVar46 = (byte)iVar47;
      bVar41 = (byte)(uVar54 - 0x30);
      if (uVar42 < 6) {
        bVar46 = (byte)(iVar47 << 4);
      }
      if ((uVar54 - 0x30 & 0xff) < 10) goto LAB_00117b88;
LAB_00117bc6:
      pbVar39 = pbVar39 + 2;
      if (uVar54 - 0x61 < 6) {
        bVar46 = bVar46 | (char)uVar54 + 0xa9U;
      }
      pbVar30 = pbVar30 + 1;
      *pbVar30 = bVar46;
      if (pbVar30 == local_4c0 + 0x27) goto LAB_00117bde;
    }
    uVar54 = (uint)*pbVar39;
    bVar46 = bVar46 * '\x10';
    bVar41 = (byte)(uVar54 - 0x30);
    if (9 < (uVar54 - 0x30 & 0xff)) goto LAB_00117bc6;
LAB_00117b88:
    pbVar39 = pbVar39 + 2;
    pbVar30 = pbVar30 + 1;
    *pbVar30 = bVar46 | bVar41;
  } while (pbVar30 != local_4c0 + 0x27);
LAB_00117bde:
  iVar47 = FUN_00116ca8(&local_50c);
  if ((iVar47 == 0) && (iVar31 = memcmp(DAT_00117ed8,local_4c0,0x28), iVar31 == 0)) {
    if (*(int *)(DAT_0019ebac + 0x20) != 0) goto LAB_00117d14;
LAB_001180f8:
    if (DAT_00194bf0 != 0) {
      puts("algoboard wake up!!!");
      printf("func:%s line:%d\n",DAT_00118260,0x471);
      FUN_00127914(0x3c9,0);
      FUN_0011b59c(*local_50c);
      usleep(1000);
      puts("read temp ");
      FUN_0011b4a4(*local_50c,"7f 55 ff 81 01 00",1);
      FUN_0011a8dc(DAT_00118258,&DAT_00197f20,0x800);
      FUN_0011a8dc(DAT_00118268,DAT_00118264,0x800);
      FUN_0011a8dc(DAT_00118270,DAT_0011826c,0x800);
      FUN_0011a8dc(DAT_00118278,DAT_00118274,0x800);
      DAT_00194bf0 = 0;
    }
  }
  else {
    DAT_00195008 = '\x01';
    memcpy(&DAT_0019500c,&DAT_00194fb8,0x50);
    memcpy(&DAT_0019af20,&DAT_00199f20,0x1000);
    FUN_001150bc(local_4c0,&DAT_00199f20);
    pcVar55 = *(char **)(iVar38 + 0x108);
    DAT_0019505c = DAT_0019507c;
    DAT_00195060 = DAT_00195080;
    DAT_00195064 = DAT_00195084;
    DAT_00195068 = DAT_00195088;
    DAT_0019506c = DAT_0019508c;
    DAT_00195070 = DAT_00195090;
    DAT_00195074 = DAT_00195094;
    DAT_00195078 = DAT_00195098;
    sVar32 = strlen(pcVar55);
    memcpy(&DAT_0019507c,pcVar55,sVar32 + 1);
    printf("work->job_id = %s\n",*(undefined4 *)(iVar38 + 0x108));
    printf("jobid_current = %s\n",&DAT_0019507c);
    printf("jobid_last = %s\n",&DAT_0019505c);
    sVar32 = strlen(*(char **)(iVar38 + 0x108));
    printf("jobid_current sizeof = %d\n",sVar32);
    if (*(int *)(DAT_0019ebac + 0x20) == 0) goto LAB_001180f8;
  }
  if (iVar47 != 0) {
    FUN_0011a8dc(DAT_00117edc,&DAT_00197f20,0x800);
    FUN_0011a8dc(DAT_00117ee4,DAT_00117ee0,0x800);
    FUN_0011a8dc(DAT_00117eec,DAT_00117ee8,0x800);
    FUN_0011a8dc(DAT_00117ef4,DAT_00117ef0,0x800);
    pthread_create(DAT_00117ef8,(pthread_attr_t *)0x0,(__start_routine *)&LAB_00116558_1,(void *)0x0
                  );
  }
LAB_00117d14:
  local_57c = &DAT_001923b8;
  if (DAT_001923bc < 0) {
    puts("bus error");
                    /* WARNING: Subroutine does not return */
    exit(-1);
  }
  DAT_0019f048 = DAT_001923bc;
  memcpy(&DAT_00194fb8,local_4c0,0x50);
  local_520 = 0;
  uStack_51c = 0;
  local_510._3_1_ = (undefined)((uint)uStack_524 >> 0x18);
  local_510._2_1_ = (undefined)((uint)uStack_524 >> 0x10);
  uVar42 = local_528 & 0xff;
  local_514._1_1_ = (byte)(local_528 >> 8);
  bVar46 = local_514._1_1_;
  uVar59 = (uint)local_514._1_1_;
  local_514._2_1_ = (byte)(local_528 >> 0x10);
  uVar56 = (uint)local_514._2_1_;
  local_510._1_1_ = (undefined)((uint)uStack_524 >> 8);
  local_514._3_1_ = (byte)(local_528 >> 0x18);
  bVar41 = local_514._3_1_;
  uVar54 = (uint)local_514._3_1_;
  local_510._0_1_ = (undefined)uStack_524;
  uVar1 = CONCAT21(CONCAT11((char)local_528,bVar46),local_514._2_1_);
  local_514 = CONCAT13((undefined)local_510,
                       CONCAT12(local_510._1_1_,CONCAT11(local_510._2_1_,local_510._3_1_)));
  local_510 = CONCAT31(uVar1,bVar41);
  memset(&local_470,0,0x400);
  dVar2 = DAT_00117ec8;
  dVar3 = DAT_00117ed0;
  if (DAT_001923c0 != 0) {
    DAT_001923c0 = 0;
    gettimeofday((timeval *)&DAT_001950f0,(__timezone_ptr_t)0x0);
    gettimeofday((timeval *)&DAT_001950f8,(__timezone_ptr_t)0x0);
    dVar2 = DAT_00117ec8;
    dVar3 = DAT_00117ed0;
  }
  while (DAT_00117ec8 = dVar2, DAT_00117ed0 = dVar3, DAT_0019c0ec != 0) {
    usleep(1000000);
    dVar2 = DAT_00117ec8;
    dVar3 = DAT_00117ed0;
  }
  local_56c = 0;
  uVar42 = uVar42 + (uVar59 + (uVar56 + uVar54 * 0x100) * 0x100) * 0x100;
  DAT_0019c0ec = 0;
  do {
    if (DAT_00195008 != '\0') {
      if (DAT_001923d8 != (undefined1 *)0x0) {
        puts("need update data----------------");
      }
      iVar31 = DAT_001923bc;
      iVar47 = 0;
      DAT_00195008 = '\0';
      puVar33 = (undefined4 *)malloc(0x50);
      if (puVar33 != (undefined4 *)0x0) {
        memset(&local_4e0,0,0x1e);
        uVar54 = local_514 & 0xff;
        *puVar33 = 0;
        if (uVar54 == 0) {
LAB_00117e52:
          uVar54 = local_514 >> 8 & 0xff;
          if (uVar54 == 0) {
LAB_00117e5c:
            uVar54 = local_514 >> 0x10 & 0xff;
            if (uVar54 == 0) {
LAB_00117e66:
              uVar54 = local_514 >> 0x18;
              if (uVar54 == 0) {
LAB_00117e70:
                uVar54 = local_510 & 0xff;
                if (uVar54 == 0) {
LAB_00117e7a:
                  uVar54 = local_510 >> 8 & 0xff;
                  if (uVar54 == 0) {
LAB_00117e84:
                    uVar54 = local_510 >> 0x10 & 0xff;
                    if (uVar54 == 0) {
LAB_00117e8e:
                      uVar54 = local_510 >> 0x18;
                      if (uVar54 == 0) {
LAB_00117e98:
                        iVar47 = 0x40;
                      }
                      else if ((int)(uVar54 << 0x18) < 0) {
                        iVar47 = 0x38;
                      }
                      else {
                        if ((int)(uVar54 << 0x19) < 0) {
                          iVar47 = 0x38;
                          goto LAB_00119686;
                        }
                        if ((int)(uVar54 << 0x1a) < 0) {
                          uVar56 = 0x38;
                          goto LAB_001196a6;
                        }
                        if ((int)(uVar54 << 0x1b) < 0) {
                          iVar47 = 0x38;
                          goto LAB_001196be;
                        }
                        if ((int)(uVar54 << 0x1c) < 0) {
                          uVar56 = 0x38;
                          goto LAB_0011989e;
                        }
                        if ((int)(uVar54 << 0x1d) < 0) {
                          iVar47 = 0x38;
                          goto LAB_0011996c;
                        }
                        if ((int)(uVar54 << 0x1e) < 0) {
                          uVar56 = 0x38;
                          goto LAB_00119974;
                        }
                        if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e98;
                        iVar47 = 0x3f;
                      }
                    }
                    else if ((int)(uVar54 << 0x18) < 0) {
                      iVar47 = 0x30;
                    }
                    else {
                      if ((int)(uVar54 << 0x19) < 0) {
                        iVar47 = 0x30;
                        goto LAB_00119686;
                      }
                      if ((int)(uVar54 << 0x1a) < 0) {
                        uVar56 = 0x30;
                        goto LAB_001196a6;
                      }
                      if ((int)(uVar54 << 0x1b) < 0) {
                        iVar47 = 0x30;
LAB_001196be:
                        iVar47 = iVar47 + 3;
                      }
                      else {
                        if ((int)(uVar54 << 0x1c) < 0) {
                          uVar56 = 0x30;
                          goto LAB_0011989e;
                        }
                        if ((int)(uVar54 << 0x1d) < 0) {
                          iVar47 = 0x30;
LAB_0011996c:
                          iVar47 = iVar47 + 5;
                        }
                        else {
                          if ((int)(uVar54 << 0x1e) < 0) {
                            uVar56 = 0x30;
                            goto LAB_00119974;
                          }
                          if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e8e;
                          iVar47 = 0x37;
                        }
                      }
                    }
                  }
                  else if ((int)(uVar54 << 0x18) < 0) {
                    iVar47 = 0x28;
                  }
                  else if ((int)(uVar54 << 0x19) < 0) {
                    iVar47 = 0x29;
                  }
                  else if ((int)(uVar54 << 0x1a) < 0) {
                    iVar47 = 0x2a;
                  }
                  else if ((int)(uVar54 << 0x1b) < 0) {
                    iVar47 = 0x2b;
                  }
                  else if ((int)(uVar54 << 0x1c) < 0) {
                    iVar47 = 0x2c;
                  }
                  else if ((int)(uVar54 << 0x1d) < 0) {
                    iVar47 = 0x2d;
                  }
                  else if ((int)(uVar54 << 0x1e) < 0) {
                    iVar47 = 0x2e;
                  }
                  else {
                    if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e84;
                    iVar47 = 0x2f;
                  }
                }
                else if ((int)(uVar54 << 0x18) < 0) {
                  iVar47 = 0x20;
                }
                else if ((int)(uVar54 << 0x19) < 0) {
                  iVar47 = 0x21;
                }
                else if ((int)(uVar54 << 0x1a) < 0) {
                  iVar47 = 0x22;
                }
                else if ((int)(uVar54 << 0x1b) < 0) {
                  iVar47 = 0x23;
                }
                else if ((int)(uVar54 << 0x1c) < 0) {
                  iVar47 = 0x24;
                }
                else if ((int)(uVar54 << 0x1d) < 0) {
                  iVar47 = 0x25;
                }
                else if ((int)(uVar54 << 0x1e) < 0) {
                  iVar47 = 0x26;
                }
                else {
                  if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e7a;
                  iVar47 = 0x27;
                }
              }
              else if ((int)(uVar54 << 0x18) < 0) {
                iVar47 = 0x18;
              }
              else if ((int)(uVar54 << 0x19) < 0) {
                iVar47 = 0x19;
              }
              else if ((int)(uVar54 << 0x1a) < 0) {
                iVar47 = 0x1a;
              }
              else if ((int)(uVar54 << 0x1b) < 0) {
                iVar47 = 0x1b;
              }
              else if ((int)(uVar54 << 0x1c) < 0) {
                iVar47 = 0x1c;
              }
              else if ((int)(uVar54 << 0x1d) < 0) {
                iVar47 = 0x1d;
              }
              else if ((int)(uVar54 << 0x1e) < 0) {
                iVar47 = 0x1e;
              }
              else {
                if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e70;
                iVar47 = 0x1f;
              }
            }
            else if ((int)(uVar54 << 0x18) < 0) {
              iVar47 = 0x10;
            }
            else if ((int)(uVar54 << 0x19) < 0) {
              iVar47 = 0x11;
            }
            else if ((int)(uVar54 << 0x1a) < 0) {
              iVar47 = 0x12;
            }
            else if ((int)(uVar54 << 0x1b) < 0) {
              iVar47 = 0x13;
            }
            else if ((int)(uVar54 << 0x1c) < 0) {
              iVar47 = 0x14;
            }
            else if ((int)(uVar54 << 0x1d) < 0) {
              iVar47 = 0x15;
            }
            else if ((int)(uVar54 << 0x1e) < 0) {
              iVar47 = 0x16;
            }
            else {
              if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e66;
              iVar47 = 0x17;
            }
          }
          else if ((int)(uVar54 << 0x18) < 0) {
            iVar47 = 8;
          }
          else if ((int)(uVar54 << 0x19) < 0) {
            iVar47 = 9;
          }
          else if ((int)(uVar54 << 0x1a) < 0) {
            iVar47 = 10;
          }
          else if ((int)(uVar54 << 0x1b) < 0) {
            iVar47 = 0xb;
          }
          else if ((int)(uVar54 << 0x1c) < 0) {
            iVar47 = 0xc;
          }
          else if ((int)(uVar54 << 0x1d) < 0) {
            iVar47 = 0xd;
          }
          else if ((int)(uVar54 << 0x1e) < 0) {
            iVar47 = 0xe;
          }
          else {
            if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e5c;
            iVar47 = 0xf;
          }
        }
        else if (-1 < (int)(uVar54 << 0x18)) {
          uVar56 = local_514 & 0x40;
          if ((local_514 & 0x40) == 0) {
            if ((local_514 & 0x20) == 0) {
              uVar56 = local_514 & 0x10;
              if ((local_514 & 0x10) == 0) {
                if ((local_514 & 8) == 0) {
                  uVar56 = local_514 & 4;
                  if ((local_514 & 4) == 0) {
                    if ((int)(uVar54 << 0x1e) < 0) {
LAB_00119974:
                      iVar47 = uVar56 + 6;
                    }
                    else {
                      if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00117e52;
                      iVar47 = 7;
                    }
                  }
                  else {
                    iVar47 = (local_514 & 8) + 5;
                  }
                }
                else {
LAB_0011989e:
                  iVar47 = uVar56 + 4;
                }
              }
              else {
                iVar47 = (local_514 & 0x20) + 3;
              }
            }
            else {
LAB_001196a6:
              iVar47 = uVar56 + 2;
            }
          }
          else {
LAB_00119686:
            iVar47 = iVar47 + 1;
          }
        }
        if (DAT_001923d8 != (undefined1 *)0x0) {
          printf("leading zero: %08X, act=%d, force=%d\n",0,iVar47,0x1e);
        }
        sprintf((char *)&local_4e0,"7f 55 ff 0d 01 %02X",10);
        iVar47 = 0;
        for (uVar54 = 0; sVar32 = strlen((char *)&local_4e0), uVar54 < sVar32; uVar54 = uVar54 + 3)
        {
          iVar47 = iVar47 + 1;
          uVar34 = strtoul((char *)((int)&local_4e0 + uVar54),(char **)0x0,0x10);
          *(char *)((int)puVar33 + uVar54 / 3) = (char)uVar34;
        }
        FUN_0011b1b0(iVar31,puVar33,iVar47,1);
        pcVar55 = "7f 55 ff 0c";
        uVar54 = 0;
        if (DAT_00195100 < 0x7f) {
          DAT_00195100 = DAT_00195100 + 1;
        }
        else {
          DAT_00195100 = 0;
        }
        do {
          uVar34 = strtoul(pcVar55,(char **)0x0,0x10);
          uVar56 = uVar54 + 3;
          *(char *)((int)puVar33 + uVar54 / 3) = (char)uVar34;
          puVar48 = DAT_00118250;
          uVar54 = uVar56;
          pcVar55 = pcVar55 + 3;
        } while (uVar56 != 0xc);
        puVar43 = puVar33 + 5;
        *(undefined *)(puVar33 + 1) = 0x39;
        uVar28 = *(undefined *)(iVar38 + 0x18a);
        puVar35 = puVar48 + -0x28;
        *(undefined *)((int)puVar33 + 5) = *(undefined *)(iVar38 + 0x189);
        *(undefined *)((int)puVar33 + 6) = uVar28;
        *(undefined4 *)((int)puVar33 + 7) = 0;
        *(undefined4 *)((int)puVar33 + 0xb) = 0;
        *(undefined4 *)((int)puVar33 + 0xf) = 0;
        *(undefined2 *)((int)puVar33 + 0x13) = 0;
        do {
          puVar48 = puVar48 + -1;
          puVar43 = (undefined4 *)((int)puVar43 + 1);
          *(undefined *)puVar43 = *puVar48;
        } while (puVar48 != puVar35);
        *(byte *)((int)puVar33 + 0x3d) = DAT_00195100;
        uVar28 = FUN_0011af7c(puVar33,0x3e);
        *(undefined *)((int)puVar33 + 0x3e) = uVar28;
        FUN_0011b1b0(iVar31,puVar33,0x3f,0);
        free(puVar33);
      }
    }
    if (*pcVar29 == '\x01') {
      if (DAT_001923d8 != (undefined1 *)0x0) {
        puts("-------------restart=1");
        return 0;
      }
      return 0;
    }
    gettimeofday(DAT_00118254,(__timezone_ptr_t)0x0);
    iVar47 = DAT_001923bc;
    dVar68 = DAT_00118230;
    if (999 < (uint)((DAT_00195104 - DAT_001950f8) * 1000 + (DAT_00195108 - DAT_001950fc) / 1000)) {
      DAT_001950f8 = DAT_00195104;
      DAT_001950fc = DAT_00195108;
      if (DAT_0019c174 != 0) {
        printf("func:%s line:%d\n",DAT_00119434,0x3b5);
        if (-1 < iVar47) {
          FUN_0011b4a4(iVar47,"7f 55 ff 80 06 00 00 00 00 00 00 59",0);
          puts("read chip_id");
          FUN_0011b4a4(iVar47,"7f 55 ff 82 01 00",1);
          puts("read temp ");
          FUN_0011b4a4(iVar47,"7f 55 ff 81 01 00",1);
        }
        usleep(1000);
        FUN_0011b4a4(DAT_001923bc,"7f 55 ff 8e  01 30",1);
        usleep(1000);
        DAT_0019c174 = 0;
      }
      iVar47 = DAT_001923bc;
      if (DAT_0019510c % 0x78 == 0) {
        printf("func:%s line:%d\n",DAT_00119434,0x3b5);
        if (-1 < iVar47) {
          FUN_0011b4a4(iVar47,"7f 55 ff 80 06 00 00 00 00 00 00 59",0);
          puts("read chip_id");
          FUN_0011b4a4(iVar47,"7f 55 ff 82 01 00",1);
          puts("read temp ");
          FUN_0011b4a4(iVar47,"7f 55 ff 81 01 00",1);
        }
        usleep(1000);
        FUN_0011b4a4(DAT_001923bc,"7f 55 ff 8e  01 30",1);
        usleep(1000);
      }
      iVar47 = DAT_001923bc;
      if ((DAT_0019510c % 600 == 0) ||
         ((DAT_0019510c / 0x3c) * 0x3c - DAT_0019510c == 0 && DAT_0019510c < 600)) {
        printf("func:%s line:%d\n",DAT_001190e4,0x3b5);
        if (-1 < iVar47) {
          FUN_0011b4a4(iVar47,"7f 55 ff 80 06 00 00 00 00 00 00 59",0);
          puts("read chip_id");
          FUN_0011b4a4(iVar47,"7f 55 ff 82 01 00",1);
          puts("read temp ");
          FUN_0011b4a4(iVar47,"7f 55 ff 81 01 00",1);
        }
        usleep(1000);
        FUN_0011b4a4(DAT_001923bc,"7f 55 ff 8e  01 30",1);
        usleep(1000);
      }
      DAT_0019510c = DAT_0019510c + 1;
      DAT_00195110 = DAT_00195110 + 1;
      DAT_00195114 = DAT_00195114 + 1;
      if (DAT_001923d8 != (undefined1 *)0x0 && DAT_00195110 == 10) {
        DAT_00195110 = 0;
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
        puVar33 = DAT_0011a144;
        iVar47 = 1;
        puVar43 = DAT_0011a144 + 0x91;
        puVar58 = (undefined8 *)(DAT_0011a144 + 0x148);
        do {
          HintPreloadData(puVar33 + 0x74);
          iVar31 = iVar47 + 1;
          printf(&DAT_0017db3c,iVar47,*puVar33,puVar33[1],*puVar58,puVar43[1],iVar47 + 0x12,
                 *(undefined8 *)(puVar33 + 0x24),puVar58[0x12],puVar43[0x13],iVar47 + 0x24,
                 *(undefined8 *)(puVar33 + 0x48),puVar58[0x24],puVar43[0x25],iVar47 + 0x36,
                 *(undefined8 *)(puVar33 + 0x6c),puVar58[0x36],puVar43[0x37]);
          puVar33 = puVar33 + 2;
          iVar47 = iVar31;
          puVar43 = puVar43 + 1;
          puVar58 = puVar58 + 1;
        } while (iVar31 != 0x13);
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
        putchar(10);
      }
      uVar54 = DAT_0019510c;
      if (DAT_0019510c % 0x78 == 0) {
        piVar51 = DAT_00119438 + 0x147;
        piVar60 = DAT_00119438 + 0x49;
        DAT_00194e40 = 0;
        piVar45 = DAT_00119438;
        do {
          piVar45 = piVar45 + 1;
          iVar47 = *piVar45;
          piVar51 = piVar51 + 1;
          *piVar51 = 1;
          DAT_00194e40 = DAT_00194e40 + iVar47 / 1000000;
        } while (piVar60 != piVar45);
        if (DAT_001923d8 != (undefined1 *)0x0) {
          printf("....................theory_power=%ld.......................\n",DAT_00194e40);
          uVar54 = DAT_0019510c;
        }
      }
      if (uVar54 == (uVar54 / 0xb4) * 0xb4) {
        DAT_00195484 = 1;
      }
      if (uVar54 % 0x3c == 0) {
        puts("GPIO_DOG2 GPIO11");
        FUN_00127914(0x3cb,1);
        usleep(1000);
        FUN_00127914(0x3cb,0);
      }
      uVar54 = local_514 & 0xff;
      if (uVar54 == 0) {
LAB_001189c4:
        uVar54 = local_514 >> 8 & 0xff;
        if (uVar54 == 0) {
LAB_001189ce:
          uVar54 = local_514 >> 0x10 & 0xff;
          if (uVar54 == 0) {
LAB_001189d8:
            uVar54 = local_514 >> 0x18;
            if (uVar54 == 0) {
LAB_001189e2:
              uVar54 = local_510 & 0xff;
              if (uVar54 == 0) {
LAB_001189ec:
                uVar54 = local_510 >> 8 & 0xff;
                if (uVar54 == 0) {
LAB_001189f6:
                  uVar54 = local_510 >> 0x10 & 0xff;
                  if (uVar54 == 0) {
LAB_00118a00:
                    uVar54 = local_510 >> 0x18;
                    if (uVar54 == 0) {
LAB_00118a0a:
                      DAT_00195488 = 0x40;
                    }
                    else if ((int)(uVar54 << 0x18) < 0) {
                      DAT_00195488 = 0x38;
                    }
                    else {
                      if ((int)(uVar54 << 0x19) < 0) {
                        iVar47 = 0x38;
                        goto LAB_00119a9a;
                      }
                      if ((int)(uVar54 << 0x1a) < 0) {
                        iVar47 = 0x38;
                        goto LAB_00119a92;
                      }
                      if ((int)(uVar54 << 0x1b) < 0) {
                        uVar56 = 0x38;
                        goto LAB_00119aa2;
                      }
                      if ((int)(uVar54 << 0x1c) < 0) {
                        iVar47 = 0x38;
                        goto LAB_00119af0;
                      }
                      if ((int)(uVar54 << 0x1d) < 0) {
                        uVar56 = 0x38;
                        goto LAB_00119ada;
                      }
                      if ((int)(uVar54 << 0x1e) < 0) {
                        iVar47 = 0x38;
                        goto LAB_00119cb8;
                      }
                      if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00118a0a;
                      DAT_00195488 = 0x3f;
                    }
                  }
                  else if ((int)(uVar54 << 0x18) < 0) {
                    DAT_00195488 = 0x30;
                  }
                  else if ((int)(uVar54 << 0x19) < 0) {
                    iVar47 = 0x30;
LAB_00119a9a:
                    DAT_00195488 = iVar47 + 1;
                  }
                  else if ((int)(uVar54 << 0x1a) < 0) {
                    iVar47 = 0x30;
LAB_00119a92:
                    DAT_00195488 = iVar47 + 2;
                  }
                  else {
                    if ((int)(uVar54 << 0x1b) < 0) {
                      uVar56 = 0x30;
                      goto LAB_00119aa2;
                    }
                    if ((int)(uVar54 << 0x1c) < 0) {
                      iVar47 = 0x30;
LAB_00119af0:
                      DAT_00195488 = iVar47 + 4;
                    }
                    else {
                      if ((int)(uVar54 << 0x1d) < 0) {
                        uVar56 = 0x30;
                        goto LAB_00119ada;
                      }
                      if ((int)(uVar54 << 0x1e) < 0) {
                        iVar47 = 0x30;
LAB_00119cb8:
                        DAT_00195488 = iVar47 + 6;
                      }
                      else {
                        if (-1 < (int)(uVar54 << 0x1f)) goto LAB_00118a00;
                        DAT_00195488 = 0x37;
                      }
                    }
                  }
                }
                else if ((int)(uVar54 << 0x18) < 0) {
                  DAT_00195488 = 0x28;
                }
                else if ((int)(uVar54 << 0x19) < 0) {
                  DAT_00195488 = 0x29;
                }
                else if ((int)(uVar54 << 0x1a) < 0) {
                  DAT_00195488 = 0x2a;
                }
                else if ((int)(uVar54 << 0x1b) < 0) {
                  DAT_00195488 = 0x2b;
                }
                else if ((int)(uVar54 << 0x1c) < 0) {
                  DAT_00195488 = 0x2c;
                }
                else if ((int)(uVar54 << 0x1d) < 0) {
                  DAT_00195488 = 0x2d;
                }
                else if ((int)(uVar54 << 0x1e) < 0) {
                  DAT_00195488 = 0x2e;
                }
                else {
                  if (-1 < (int)(uVar54 << 0x1f)) goto LAB_001189f6;
                  DAT_00195488 = 0x2f;
                }
              }
              else if ((int)(uVar54 << 0x18) < 0) {
                DAT_00195488 = 0x20;
              }
              else if ((int)(uVar54 << 0x19) < 0) {
                DAT_00195488 = 0x21;
              }
              else if ((int)(uVar54 << 0x1a) < 0) {
                DAT_00195488 = 0x22;
              }
              else if ((int)(uVar54 << 0x1b) < 0) {
                DAT_00195488 = 0x23;
              }
              else if ((int)(uVar54 << 0x1c) < 0) {
                DAT_00195488 = 0x24;
              }
              else if ((int)(uVar54 << 0x1d) < 0) {
                DAT_00195488 = 0x25;
              }
              else if ((int)(uVar54 << 0x1e) < 0) {
                DAT_00195488 = 0x26;
              }
              else {
                if (-1 < (int)(uVar54 << 0x1f)) goto LAB_001189ec;
                DAT_00195488 = 0x27;
              }
            }
            else if ((int)(uVar54 << 0x18) < 0) {
              DAT_00195488 = 0x18;
            }
            else if ((int)(uVar54 << 0x19) < 0) {
              DAT_00195488 = 0x19;
            }
            else if ((int)(uVar54 << 0x1a) < 0) {
              DAT_00195488 = 0x1a;
            }
            else if ((int)(uVar54 << 0x1b) < 0) {
              DAT_00195488 = 0x1b;
            }
            else if ((int)(uVar54 << 0x1c) < 0) {
              DAT_00195488 = 0x1c;
            }
            else if ((int)(uVar54 << 0x1d) < 0) {
              DAT_00195488 = 0x1d;
            }
            else if ((int)(uVar54 << 0x1e) < 0) {
              DAT_00195488 = 0x1e;
            }
            else {
              if (-1 < (int)(uVar54 << 0x1f)) goto LAB_001189e2;
              DAT_00195488 = 0x1f;
            }
          }
          else if ((int)(uVar54 << 0x18) < 0) {
            DAT_00195488 = 0x10;
          }
          else if ((int)(uVar54 << 0x19) < 0) {
            DAT_00195488 = 0x11;
          }
          else if ((int)(uVar54 << 0x1a) < 0) {
            DAT_00195488 = 0x12;
          }
          else if ((int)(uVar54 << 0x1b) < 0) {
            DAT_00195488 = 0x13;
          }
          else if ((int)(uVar54 << 0x1c) < 0) {
            DAT_00195488 = 0x14;
          }
          else if ((int)(uVar54 << 0x1d) < 0) {
            DAT_00195488 = 0x15;
          }
          else if ((int)(uVar54 << 0x1e) < 0) {
            DAT_00195488 = 0x16;
          }
          else {
            if (-1 < (int)(uVar54 << 0x1f)) goto LAB_001189d8;
            DAT_00195488 = 0x17;
          }
        }
        else if ((int)(uVar54 << 0x18) < 0) {
          DAT_00195488 = 8;
        }
        else if ((int)(uVar54 << 0x19) < 0) {
          DAT_00195488 = 9;
        }
        else if ((int)(uVar54 << 0x1a) < 0) {
          DAT_00195488 = 10;
        }
        else if ((int)(uVar54 << 0x1b) < 0) {
          DAT_00195488 = 0xb;
        }
        else if ((int)(uVar54 << 0x1c) < 0) {
          DAT_00195488 = 0xc;
        }
        else if ((int)(uVar54 << 0x1d) < 0) {
          DAT_00195488 = 0xd;
        }
        else if ((int)(uVar54 << 0x1e) < 0) {
          DAT_00195488 = 0xe;
        }
        else {
          if (-1 < (int)(uVar54 << 0x1f)) goto LAB_001189ce;
          DAT_00195488 = 0xf;
        }
LAB_00118a0c:
        iVar47 = 0;
        DAT_0019548c = 0x22;
        uVar54 = 1;
        iVar31 = 0;
        do {
          bVar66 = CARRY4(uVar54,uVar54);
          uVar54 = uVar54 * 2;
          iVar31 = iVar31 + 1;
          iVar47 = iVar47 * 2 + (uint)bVar66;
        } while (iVar31 != DAT_00195488);
        dVar68 = (double)__aeabi_l2d(uVar54,iVar47);
        DAT_0019c1e8 = dVar68 * DAT_00118d38;
      }
      else {
        if (-1 < (int)(uVar54 << 0x18)) {
          if ((local_514 & 0x40) == 0) {
            uVar56 = local_514 & 0x20;
            if ((local_514 & 0x20) == 0) {
              if ((local_514 & 0x10) == 0) {
                uVar56 = local_514 & 8;
                if ((local_514 & 8) == 0) {
                  if ((local_514 & 4) == 0) {
                    if ((local_514 & 2) == 0) {
                      if (-1 < (int)(uVar54 << 0x1f)) goto LAB_001189c4;
                      DAT_00195488 = (local_514 & 2) + 7;
                    }
                    else {
                      DAT_00195488 = (local_514 & 4) + 6;
                    }
                  }
                  else {
LAB_00119ada:
                    DAT_00195488 = uVar56 + 5;
                  }
                }
                else {
                  DAT_00195488 = (local_514 & 0x10) + 4;
                }
              }
              else {
LAB_00119aa2:
                DAT_00195488 = uVar56 + 3;
              }
            }
            else {
              DAT_00195488 = (local_514 & 0x40) + 2;
            }
          }
          else {
            DAT_00195488 = 1;
          }
          goto LAB_00118a0c;
        }
        DAT_00195488 = 0;
        DAT_0019548c = 0x22;
        DAT_0019c1e8 = DAT_0011a4f8;
      }
      DAT_00195490 = 0;
      if (DAT_00195114 % 300 == 0) {
        if (DAT_001923c4 == 0x22) {
          DAT_00195490 = 0;
          piVar45 = DAT_00119d10;
          do {
            piVar45 = piVar45 + 1;
            DAT_00195490 = DAT_00195490 + *piVar45;
          } while (piVar45 != DAT_00119d10 + 0x48);
          local_558 = (double *)&DAT_0019f020;
          pdVar50 = DAT_00119d14 + 4;
          local_548 = DAT_00119d14 + 8;
          local_54c = DAT_00119d14;
          DAT_001955b8 = DAT_00195490 - DAT_001955bc;
          local_570 = DAT_00119d14 + 0xc;
          pdVar63 = (double *)&DAT_0019f050;
          iVar47 = 0;
          pdVar52 = pdVar50;
          pdVar53 = DAT_00119d14;
          pdVar61 = local_548;
          pdVar65 = local_570;
          do {
            uVar5 = DAT_00119d18;
            dVar67 = *pdVar53;
            pdVar53 = pdVar53 + 1;
            iVar36 = iVar47 + 1;
            dVar69 = *pdVar63;
            pdVar63 = pdVar63 + 1;
            dVar68 = *local_558;
            local_558 = local_558 + 1;
            dVar71 = *pdVar61;
            pdVar61 = pdVar61 + 1;
            *pdVar52 = dVar68 - dVar67;
            pdVar52 = pdVar52 + 1;
            *pdVar65 = dVar69 - dVar71;
            pdVar65 = pdVar65 + 1;
            printf("board_real_time%d = %f\n",iVar47,uVar5);
            iVar31 = DAT_00195114;
            dVar68 = DAT_00119cf8;
            iVar47 = iVar36;
          } while (iVar36 != 4);
          local_558 = (double *)DAT_001955b8;
          local_554 = (int)DAT_001955b8 >> 0x1f;
          if (0 < DAT_0019548c) {
            iVar47 = 0;
            uVar54 = 1;
            iVar36 = 0;
            do {
              bVar66 = CARRY4(uVar54,uVar54);
              uVar54 = uVar54 * 2;
              iVar47 = iVar47 + 1;
              iVar36 = iVar36 * 2 + (uint)bVar66;
            } while (DAT_0019548c != iVar47);
            local_554 = uVar54 * local_554 + DAT_001955b8 * iVar36 +
                        (int)((ulonglong)DAT_001955b8 * (ulonglong)uVar54 >> 0x20);
            local_558 = (double *)((ulonglong)DAT_001955b8 * (ulonglong)uVar54);
          }
          pdVar52 = (double *)&DAT_0019c198;
          pdVar53 = (double *)&DAT_0019c1b8;
          uVar77 = __aeabi_ldivmod(local_558,local_554,DAT_00195114,DAT_00195114 >> 0x1f);
          DAT_00195640 = (undefined1 *)
                         __aeabi_ldivmod((int)uVar77,(int)((ulonglong)uVar77 >> 0x20),DAT_00119d00,
                                         DAT_00119d04);
          iVar47 = 0;
          do {
            dVar69 = *pdVar50;
            pdVar50 = pdVar50 + 1;
            dVar67 = (double)(longlong)iVar31 * dVar68;
            dVar71 = *local_570;
            local_570 = local_570 + 1;
            if (DAT_001923c4 < 1) {
              *pdVar53 = dVar69 / dVar67;
            }
            else {
              iVar36 = 0;
              uVar54 = 1;
              iVar31 = 0;
              do {
                bVar66 = CARRY4(uVar54,uVar54);
                uVar54 = uVar54 * 2;
                iVar36 = iVar36 + 1;
                iVar31 = iVar31 * 2 + (uint)bVar66;
              } while (DAT_001923c4 != iVar36);
              dVar74 = (double)__aeabi_l2d(uVar54,iVar31);
              iVar49 = 0;
              uVar54 = 1;
              iVar31 = 0;
              *pdVar53 = (dVar74 * dVar69) / dVar67;
              do {
                bVar66 = CARRY4(uVar54,uVar54);
                uVar54 = uVar54 * 2;
                iVar49 = iVar49 + 1;
                iVar31 = iVar31 * 2 + (uint)bVar66;
              } while (iVar49 != iVar36);
              dVar69 = (double)__aeabi_l2d(uVar54,iVar31);
              dVar71 = dVar71 * dVar69;
            }
            iVar49 = iVar47 + 1;
            pdVar53 = pdVar53 + 1;
            *pdVar52 = dVar71 / dVar67;
            pdVar52 = pdVar52 + 1;
            printf("board_real_power%d = %f\n",iVar47,&DAT_0019c1b8);
            iVar36 = DAT_0019ebac;
            puVar40 = DAT_00195640;
            iVar47 = iVar49;
            iVar31 = DAT_00195114;
          } while (iVar49 != 4);
          if (DAT_001923d8 == (undefined1 *)0x0) {
            *(undefined4 *)(DAT_0019ebac + 0x28) = 1;
            *(undefined1 **)(iVar36 + 0x64c) = puVar40;
          }
          else {
            printf("............diff_num=%d............\n",DAT_0019548c);
            printf("............diff_num_last=%d............\n",DAT_001923c4);
            printf("............khs1=%d............\n",DAT_00195640);
            printf("............suc_nonce_num=%d............\n",DAT_00195490);
            printf("............stas_total_last=%d............\n",DAT_001955bc);
            printf("............time_nonce=%d............\n",DAT_001955b8);
            printf("............diff_num1=%d............\n",DAT_0019548c);
            uVar54 = 1;
            iVar31 = 0;
            iVar47 = 0;
            if (0 < DAT_0019548c) {
              do {
                bVar66 = CARRY4(uVar54,uVar54);
                uVar54 = uVar54 * 2;
                iVar47 = iVar47 + 1;
                iVar31 = iVar31 * 2 + (uint)bVar66;
              } while (DAT_0019548c != iVar47);
            }
            printf("............diff_num2=%lld............\n",DAT_0019548c,uVar54,iVar31);
            printf("............init_powersec=%d............\n",DAT_00195114);
            iVar47 = DAT_0019ebac;
            puVar40 = DAT_001923d8;
            *(undefined1 **)(DAT_0019ebac + 0x64c) = DAT_00195640;
            *(undefined4 *)(iVar47 + 0x28) = 1;
            if (puVar40 != (undefined1 *)0x0) {
              printf("............khs2=%d............\n");
              printf("............lbs_miner->rt_pow=%d............\n",
                     *(undefined4 *)(DAT_0019ebac + 0x64c));
            }
          }
        }
        else {
LAB_00118a78:
          DAT_00195490 = 0;
          if (DAT_00195114 < 0x78) {
            piVar45 = DAT_00118d48;
            do {
              piVar45 = piVar45 + 1;
              DAT_00195490 = DAT_00195490 + *piVar45;
            } while (piVar45 != DAT_00118d48 + 0x48);
            iVar47 = 0x22;
            if (DAT_001923d8 != (undefined1 *)0x0) {
              printf("............diff_num_last=%d............\n");
              printf("............suc_nonce_num=%d............\n",DAT_00195490);
              printf("............stas_total_last=%d............\n",DAT_001955bc);
              printf("............time_nonce=%d............\n",DAT_001955b8);
              printf("............diff_num1=%d............\n",DAT_0019548c);
              if (DAT_0019548c < 1) {
                uVar54 = 1;
                iVar31 = 0;
                iVar47 = extraout_r1_00;
              }
              else {
                iVar47 = 0;
                uVar54 = 1;
                iVar31 = 0;
                do {
                  bVar66 = CARRY4(uVar54,uVar54);
                  uVar54 = uVar54 * 2;
                  iVar47 = iVar47 + 1;
                  iVar31 = iVar31 * 2 + (uint)bVar66;
                } while (DAT_0019548c != iVar47);
              }
              printf("............diff_num2=%lld............\n",iVar47,uVar54,iVar31);
              printf("............init_powersec=%d............\n",DAT_00195114);
              iVar47 = DAT_0019548c;
            }
            uVar5 = DAT_0019f050._4_4_;
            DAT_001955bc = DAT_00195490;
            puVar33 = DAT_00118d4c;
            DAT_00195114 = 0;
            DAT_001923c4 = iVar47;
            *DAT_00118d4c = (undefined4)DAT_0019f050;
            puVar33[1] = uVar5;
            uVar7 = DAT_0019f05c;
            uVar6 = DAT_0019f020._4_4_;
            uVar5 = (undefined4)DAT_0019f020;
            puVar33[2] = _DAT_0019f058;
            puVar33[3] = uVar7;
            puVar33[-0x10] = uVar5;
            puVar33[-0xf] = uVar6;
            uVar7 = DAT_0019f06c;
            uVar6 = DAT_0019f064;
            uVar5 = DAT_0019f060;
            puVar33[6] = DAT_0019f068;
            puVar33[7] = uVar7;
            puVar33[4] = uVar5;
            puVar33[5] = uVar6;
            uVar9 = DAT_0019f03c;
            uVar8 = DAT_0019f038;
            uVar7 = DAT_0019f034;
            uVar6 = DAT_0019f02c;
            uVar5 = _DAT_0019f028;
            puVar33[-0xc] = DAT_0019f030;
            puVar33[-0xb] = uVar7;
            puVar33[-0xe] = uVar5;
            puVar33[-0xd] = uVar6;
            puVar33[-10] = uVar8;
            puVar33[-9] = uVar9;
            dVar68 = DAT_00118230;
            goto joined_r0x00118018;
          }
          piVar45 = DAT_00118d48;
          do {
            piVar45 = piVar45 + 1;
            DAT_00195490 = DAT_00195490 + *piVar45;
          } while (piVar45 != DAT_00118d48 + 0x48);
          local_548 = DAT_001199b0 + 8;
          pdVar50 = DAT_001199b0 + 0xc;
          pdVar64 = (double *)&DAT_0019f020;
          DAT_001955b8 = DAT_00195490 - DAT_001955bc;
          pdVar62 = (double *)&DAT_0019f050;
          pdVar63 = DAT_001199b0 + 4;
          local_54c = DAT_001199b0;
          iVar47 = 0;
          pdVar52 = pdVar63;
          pdVar53 = local_548;
          pdVar61 = DAT_001199b0;
          pdVar65 = pdVar50;
          do {
            uVar5 = DAT_001199b4;
            dVar68 = *pdVar64;
            pdVar64 = pdVar64 + 1;
            dVar67 = *pdVar61;
            pdVar61 = pdVar61 + 1;
            iVar49 = iVar47 + 1;
            dVar69 = *pdVar62;
            pdVar62 = pdVar62 + 1;
            dVar71 = *pdVar53;
            pdVar53 = pdVar53 + 1;
            *pdVar52 = dVar68 - dVar67;
            pdVar52 = pdVar52 + 1;
            *pdVar65 = dVar69 - dVar71;
            pdVar65 = pdVar65 + 1;
            printf("board_real_time%d = %f\n",iVar47,uVar5);
            iVar36 = DAT_00195114;
            iVar31 = DAT_001923c4;
            dVar68 = DAT_001199a0;
            iVar47 = iVar49;
          } while (iVar49 != 4);
          iVar47 = (int)DAT_001955b8 >> 0x1f;
          uVar54 = DAT_001955b8;
          if (0 < DAT_001923c4) {
            iVar57 = 0;
            uVar56 = 1;
            iVar49 = 0;
            do {
              bVar66 = CARRY4(uVar56,uVar56);
              uVar56 = uVar56 * 2;
              iVar57 = iVar57 + 1;
              iVar49 = iVar49 * 2 + (uint)bVar66;
            } while (DAT_001923c4 != iVar57);
            uVar54 = (uint)((ulonglong)DAT_001955b8 * (ulonglong)uVar56);
            iVar47 = (int)((ulonglong)DAT_001955b8 * (ulonglong)uVar56 >> 0x20) +
                     uVar56 * iVar47 + DAT_001955b8 * iVar49;
          }
          pdVar52 = (double *)&DAT_0019c198;
          uVar77 = __aeabi_ldivmod(uVar54,iVar47,DAT_00195114,DAT_00195114 >> 0x1f);
          DAT_00195640 = (undefined1 *)
                         __aeabi_ldivmod((int)uVar77,(int)((ulonglong)uVar77 >> 0x20),DAT_001199a8,
                                         DAT_001199ac);
          iVar47 = 0;
          do {
            dVar69 = *pdVar63;
            pdVar63 = pdVar63 + 1;
            dVar71 = *pdVar50;
            pdVar50 = pdVar50 + 1;
            dVar67 = (double)(longlong)iVar36 * dVar68;
            if (iVar31 < 1) {
              (&DAT_0019c1b8)[iVar47] = dVar69 / dVar67;
            }
            else {
              iVar49 = 0;
              uVar54 = 1;
              iVar36 = 0;
              do {
                bVar66 = CARRY4(uVar54,uVar54);
                uVar54 = uVar54 * 2;
                iVar49 = iVar49 + 1;
                iVar36 = iVar36 * 2 + (uint)bVar66;
              } while (iVar49 != iVar31);
              dVar74 = (double)__aeabi_l2d(uVar54,iVar36);
              iVar49 = 0;
              uVar54 = 1;
              iVar36 = 0;
              (&DAT_0019c1b8)[iVar47] = (dVar74 * dVar69) / dVar67;
              do {
                bVar66 = CARRY4(uVar54,uVar54);
                uVar54 = uVar54 * 2;
                iVar49 = iVar49 + 1;
                iVar36 = iVar36 * 2 + (uint)bVar66;
              } while (iVar49 != iVar31);
              dVar69 = (double)__aeabi_l2d(uVar54,iVar36);
              dVar71 = dVar71 * dVar69;
            }
            iVar57 = iVar47 + 1;
            *pdVar52 = dVar71 / dVar67;
            pdVar52 = pdVar52 + 1;
            printf("board_real_power%d = %f\n",iVar47,&DAT_0019c1b8);
            iVar49 = DAT_0019ebac;
            puVar40 = DAT_00195640;
            iVar47 = iVar57;
            iVar31 = DAT_001923c4;
            iVar36 = DAT_00195114;
          } while (iVar57 != 4);
          if (DAT_001923d8 == (undefined1 *)0x0) {
            *(undefined4 *)(DAT_0019ebac + 0x28) = 1;
            *(undefined1 **)(iVar49 + 0x64c) = puVar40;
          }
          else {
            printf("............diff_num=%d............\n",DAT_0019548c);
            printf("............diff_num_last=%d............\n",DAT_001923c4);
            printf("............khs1=%d............\n",DAT_00195640);
            printf("............suc_nonce_num=%d............\n",DAT_00195490);
            printf("............stas_total_last=%d............\n",DAT_001955bc);
            printf("............time_nonce=%d............\n",DAT_001955b8);
            printf("............diff_num1=%d............\n",DAT_0019548c);
            if (DAT_0019548c < 1) {
              uVar54 = 1;
              iVar31 = 0;
              iVar47 = extraout_r1;
            }
            else {
              iVar47 = 0;
              uVar54 = 1;
              iVar31 = 0;
              do {
                bVar66 = CARRY4(uVar54,uVar54);
                uVar54 = uVar54 * 2;
                iVar47 = iVar47 + 1;
                iVar31 = iVar31 * 2 + (uint)bVar66;
              } while (DAT_0019548c != iVar47);
            }
            printf("............diff_num2=%lld............\n",iVar47,uVar54,iVar31);
            printf("............init_powersec=%d............\n",DAT_00195114);
            iVar47 = DAT_0019ebac;
            puVar40 = DAT_001923d8;
            *(undefined1 **)(DAT_0019ebac + 0x64c) = DAT_00195640;
            *(undefined4 *)(iVar47 + 0x28) = 1;
            if (puVar40 != (undefined1 *)0x0) {
              printf("............khs2=%d............\n");
              printf("............lbs_miner->rt_pow=%d............\n",
                     *(undefined4 *)(DAT_0019ebac + 0x64c));
            }
          }
          if (0x21 < DAT_0019548c) {
            puVar40 = local_57c;
          }
          if (0x21 < DAT_0019548c) {
            *(int *)(puVar40 + 0xc) = DAT_0019548c;
          }
        }
        uVar7 = DAT_0019f050._4_4_;
        uVar6 = DAT_0019f020._4_4_;
        uVar5 = (undefined4)DAT_0019f020;
        DAT_00195114 = 0;
        DAT_001955bc = DAT_00195490;
        *(undefined4 *)local_548 = (undefined4)DAT_0019f050;
        *(undefined4 *)((int)local_548 + 4) = uVar7;
        uVar8 = DAT_0019f05c;
        uVar7 = _DAT_0019f058;
        *(undefined4 *)local_54c = uVar5;
        *(undefined4 *)((int)local_54c + 4) = uVar6;
        uVar6 = DAT_0019f02c;
        uVar5 = _DAT_0019f028;
        *(undefined4 *)(local_548 + 1) = uVar7;
        *(undefined4 *)((int)local_548 + 0xc) = uVar8;
        *(undefined4 *)(local_54c + 1) = uVar5;
        *(undefined4 *)((int)local_54c + 0xc) = uVar6;
        uVar11 = DAT_0019f06c;
        uVar10 = DAT_0019f068;
        uVar9 = DAT_0019f064;
        uVar8 = DAT_0019f03c;
        uVar7 = DAT_0019f038;
        uVar6 = DAT_0019f034;
        uVar5 = DAT_0019f030;
        *(undefined4 *)(local_548 + 2) = DAT_0019f060;
        *(undefined4 *)((int)local_548 + 0x14) = uVar9;
        *(undefined4 *)(local_54c + 2) = uVar5;
        *(undefined4 *)((int)local_54c + 0x14) = uVar6;
        *(undefined4 *)(local_548 + 3) = uVar10;
        *(undefined4 *)((int)local_548 + 0x1c) = uVar11;
        *(undefined4 *)(local_54c + 3) = uVar7;
        *(undefined4 *)((int)local_54c + 0x1c) = uVar8;
        dVar68 = DAT_00118230;
      }
      else {
        dVar68 = DAT_00118230;
        if (DAT_001923c4 != 0x22) goto LAB_00118a78;
      }
    }
joined_r0x00118018:
    while (DAT_00118230 = dVar68, DAT_0019c0ec != 0) {
      usleep(1000000);
      dVar68 = DAT_00118230;
    }
    usleep(1000);
    iVar47 = DAT_00118258;
    dVar71 = DAT_00118238;
    iVar31 = 0;
    FUN_001176ec(DAT_001923bc,DAT_00118258);
    dVar67 = DAT_00118248;
    dVar69 = DAT_00118240;
LAB_0011805c:
    do {
      uVar59 = FUN_0011abac(iVar47);
      uVar54 = local_520;
      uVar56 = uStack_51c;
      while (local_520 = uVar54, uStack_51c = uVar56, 0xc < uVar59) {
        FUN_0011aa08(iVar47,&local_470,1);
        if (local_470 != 'U') goto LAB_0011805c;
        FUN_0011aa08(iVar47,&local_46f,1);
        if (local_46f == '\x7f') {
          iVar36 = FUN_0011aa08(iVar47,&local_46e,0xb);
          if (iVar36 == 0) goto LAB_0011805c;
          if (DAT_001923d8 != (undefined1 *)0x0) {
            printf("command from channel%d\n",iVar31 + 1);
            FUN_0011b120("bf----",&local_470,0xd);
          }
          uVar56 = (uint)local_464;
          uVar54 = FUN_0011af7c(&local_470,0xc);
          if (uVar56 != uVar54) {
            puts("checksum error!");
            DAT_00195790 = DAT_00195790 + 1;
            goto LAB_0011805c;
          }
          if ((int)((uint)local_465 << 0x18) < 0) {
            if (local_465 == 0x80) {
              uVar54 = (uint)local_466;
              iVar36 = ((uint)bStack_469 * 0x10000 + (uint)bStack_468 * 0x100 + (uint)bStack_467 +
                       (uint)bStack_46a * 0x1000000) * 10;
              if (DAT_001923d8 != (undefined1 *)0x0) {
                FUN_001165f8(6,"%02X noncecnt: %d, pll : %d",uVar54,
                             (uint)local_46b + (uint)local_46c * 0x100,iVar36);
                uVar54 = (uint)local_466;
              }
              (&DAT_00194e44)[uVar54] = iVar36;
            }
            else if (local_465 == 0x81) {
              uVar56 = (uint)local_466;
              uVar54 = (uint)bStack_468 * 0x100 + (uint)bStack_469 * 0x10000 + (uint)bStack_467;
              fVar75 = (float)(dVar69 + ((double)(longlong)(int)(uVar54 & 0xfff) * dVar3 - 0.5) *
                                        dVar71);
              fVar76 = (float)(dVar69 + ((double)(longlong)(int)(uVar54 >> 0xc) * dVar3 - 0.5) *
                                        dVar71);
              if (DAT_001923d8 == (undefined1 *)0x0) {
                if (fVar75 == fVar76 || fVar75 < fVar76 != (NAN(fVar75) || NAN(fVar76))) {
                  dVar74 = (double)fVar75;
                  *(double *)(&DAT_00194bf8 + uVar56 * 8) = dVar74;
                }
                else {
                  fVar73 = fVar75 - fVar76;
                  if (fVar73 == 5.0 || fVar73 < 5.0 != NAN(fVar73)) {
                    puVar40 = (undefined1 *)0x0;
                    dVar74 = (double)fVar75;
                    goto LAB_00118b90;
                  }
                  dVar74 = (double)fVar76;
                  *(double *)(&DAT_00194bf8 + uVar56 * 8) = dVar74;
                }
              }
              else {
                dVar74 = (double)fVar75;
                FUN_001165f8(6,"chip%d temp %02X:tp0:%3.1f | tp1:%3.1f",uVar56,uVar56,dVar74);
                uVar56 = (uint)local_466;
                puVar40 = DAT_001923d8;
                if ((fVar75 != fVar76 && fVar75 < fVar76 == (NAN(fVar75) || NAN(fVar76))) &&
                   (fVar75 = fVar75 - fVar76, fVar75 != 5.0 && fVar75 < 5.0 == NAN(fVar75))) {
                  dVar74 = (double)fVar76;
                }
LAB_00118b90:
                *(double *)(&DAT_00194bf8 + uVar56 * 8) = dVar74;
                if (puVar40 != (undefined1 *)0x0) {
                  printf("chip%d_flage=%d\n",uVar56,(&DAT_00195360)[uVar56]);
                }
              }
              printf(".........user_fan_flag2=%d.........\n",DAT_001923dc);
              pdVar52 = DAT_00119d0c;
              if ((DAT_00195484 != 0) && (DAT_001923dc != 0)) {
                DAT_00195484 = 0;
                pdVar53 = DAT_00119d08;
                dVar72 = DAT_00194c00;
                do {
                  dVar70 = *pdVar53;
                  pdVar53 = pdVar53 + 1;
                  if (dVar72 < dVar70 != (NAN(dVar72) || NAN(dVar70))) {
                    dVar72 = dVar70;
                  }
                } while (pdVar53 != DAT_00119d08 + 0x47);
                *DAT_00119d0c = dVar72;
                putchar(10);
                putchar(10);
                putchar(10);
                putchar(10);
                printf(&DAT_0017dedc);
                dVar72 = *pdVar52;
                if (dVar72 < DAT_00119ce0 == (NAN(dVar72) || NAN(DAT_00119ce0))) {
                  DAT_001923e0 = 0;
                  DAT_00195784 = 0;
                  DAT_00195780 = 1;
                  FUN_00127ffc(0xff,0xffffffff);
                  DAT_0019c170 = 100;
                }
                else if (((dVar72 == DAT_00119ce8 ||
                           dVar72 < DAT_00119ce8 != (NAN(dVar72) || NAN(DAT_00119ce8))) ||
                         (DAT_001923e0 == 0)) &&
                        ((-1 < (int)((uint)(dVar72 < DAT_00119ce8) << 0x1f) || (DAT_00195780 == 0)))
                        ) {
                  if (((int)((uint)(dVar72 < DAT_00119cf0) << 0x1f) < 0) && (DAT_00195784 != 0)) {
                    DAT_001923e0 = 1;
                    DAT_00195780 = 0;
                    DAT_00195784 = 0;
                    FUN_00127ffc(0,0xffffffff);
                    DAT_0019c170 = 0;
                  }
                }
                else {
                  DAT_001923e0 = 0;
                  DAT_00195780 = 0;
                  DAT_00195784 = 1;
                  FUN_00127ffc(0x7f,0xffffffff);
                  DAT_0019c170 = 0x32;
                }
              }
              uVar54 = (uint)local_466;
              if ((&DAT_00195360)[uVar54] != 0) {
                if (dVar74 < dVar67 == (NAN(dVar74) || NAN(dVar67))) {
                  DAT_0019c0c8 = 1;
                  FUN_00116684();
                  uVar54 = (uint)local_466;
                }
                if ((int)((uint)(dVar74 < DAT_00118d40) << 0x1f) < 0) {
                  DAT_0019c0c8 = 0;
                  FUN_001167fc();
                  uVar54 = (uint)local_466;
                }
                (&DAT_00195360)[uVar54] = 0;
              }
            }
            else if (local_465 == 0x8e) {
              dVar74 = (((double)(longlong)((int)((uint)local_46d + (uint)local_46e * 0x100) >> 2) *
                         6.0 - 3.0) * dVar2 - 1.0) * dVar68;
              if (DAT_001923d8 != (undefined1 *)0x0) {
                printf("bf[2]=%02x\n");
                printf("bf[3]=%02x\n",(uint)local_46d);
                if (DAT_001923d8 != (undefined1 *)0x0) {
                  printf("chip%d voltage V=%f\n",(uint)local_466,SUB84(dVar74,0),
                         (int)((ulonglong)dVar74 >> 0x20));
                }
              }
              pdVar52 = DAT_001190e0;
              *DAT_001190e0 = dVar74;
              pdVar52[local_466 - 0xce] = dVar74;
            }
            else if (local_465 == 0x82) {
              local_4e0 = CONCAT13(bStack_468,CONCAT12(bStack_469,CONCAT11(bStack_46a,local_46b)));
              local_4d8 = 0;
              local_4dc = (uint)bStack_467;
              if (DAT_001923d8 != (undefined1 *)0x0) {
                FUN_001165f8(6,"model %02X: %s",local_466,&local_4e0);
              }
            }
            else {
              FUN_001165f8(6,"unknown command: %02X");
            }
            goto LAB_0011805c;
          }
          uVar56 = (uint)local_46e;
          uVar59 = (uint)local_46d;
          DAT_00195644 = local_46e;
          bVar46 = local_46e >> 4;
          bVar41 = local_46d >> 4;
          uVar37 = (uint)bVar46 | (uVar59 & 0xf) << 4;
          uVar54 = (uint)bVar41 | (uVar56 & 0xf) << 4;
          *(int *)(&DAT_00195648 + uVar56 * 4) = *(int *)(&DAT_00195648 + uVar56 * 4) + 1;
          local_46e = (byte)uVar37;
          local_46d = (byte)uVar54;
          iVar36 = ((uint)bVar46 << 4 | uVar56 & 0xf) - 1;
          uVar56 = ((uint)local_46c | (uVar54 | uVar37 << 8) << 8) << 8;
          HintPreloadData(&DAT_0019f058 + iVar31 * 8);
          (&DAT_0019f050)[iVar31] = (double)(&DAT_0019f050)[iVar31] + 1.0;
          uVar54 = (uint)bStack_469 | ((uint)bStack_46a | (local_46b | uVar56) << 8) << 8;
          uVar56 = (uVar56 >> 0x10) +
                   ((CONCAT11(bStack_467,bStack_468) & 0xff) << 8 | (uint)bStack_467) * 0x10000;
          local_520 = uVar54;
          uStack_51c = uVar56;
          if (DAT_001923d8 != (undefined1 *)0x0) {
            printf("block=%d, chip=%d, core=%d, nonce=%0llX, dup=%d\n",(uint)bVar41,iVar36,
                   uVar59 & 0xf,uVar54);
          }
          iVar36 = iVar36 * 0x80;
          *(int *)(&DAT_00195b20 + iVar36) = *(int *)(&DAT_00195b20 + iVar36) + 1;
          break;
        }
        puts("not 55ff");
        uVar59 = FUN_0011abac(iVar47);
        uVar54 = local_520;
        uVar56 = uStack_51c;
      }
      puVar4 = DAT_0011825c;
      if ((uVar54 != 0 || uVar56 != 0) && (DAT_0011825c[1] != uVar56 || *DAT_0011825c != uVar54)) {
        __src = DAT_0011825c + -0x1ee;
        *DAT_0011825c = uVar54;
        puVar4[1] = uVar56;
        memcpy(local_4c0,__src,0x50);
        local_56c = local_56c + 1;
        local_478 = local_520;
        local_474 = uStack_51c;
        FUN_0011b120("hh----",local_4c0,0x50);
        memset(&local_500,0,0x20);
        usleep(1000);
        FUN_001151a8(local_4c0,&DAT_00199f20,&local_500);
        printf("heavy_hash=%d\n",local_56c);
        FUN_0011b120("hash32=",&local_500,0x20);
        uVar24 = local_4f0;
        uVar23 = local_4f2;
        uVar22 = local_4f3;
        uVar21 = local_4f4;
        uVar20 = local_4f5;
        uVar19 = local_4f6;
        uVar18 = local_4f7;
        uVar28 = local_4f8;
        bVar17 = local_4f9;
        bVar16 = local_4fa;
        bVar15 = local_4fb;
        bVar14 = local_4fc;
        bVar13 = local_4fd;
        bVar12 = local_4fe;
        bVar41 = local_4ff;
        bVar46 = local_500;
        local_500 = local_4e1;
        local_4ff = local_4e2;
        local_4e1 = bVar46;
        local_4e2 = bVar41;
        local_4fe = local_4e3;
        local_4fd = local_4e4;
        local_4e3 = bVar12;
        local_4e4 = bVar13;
        local_4fc = local_4e5;
        local_4e5 = bVar14;
        local_4fb = local_4e6;
        local_4e6 = bVar15;
        local_4fa = local_4e7;
        local_4f9 = local_4e8;
        local_4e8 = bVar17;
        local_4e7 = bVar16;
        local_4f8 = local_4e9;
        local_4f7 = local_4ea;
        local_4e9 = uVar28;
        local_4ea = uVar18;
        local_4f6 = local_4eb;
        local_4f5 = local_4ec;
        local_4eb = uVar19;
        local_4ec = uVar20;
        local_4f4 = local_4ed;
        local_4ed = uVar21;
        local_4f3 = local_4ee;
        local_4ee = uVar22;
        local_4f0 = local_4f1;
        local_4f2 = local_4ef;
        local_4ef = uVar23;
        local_4f1 = uVar24;
        FUN_0011b120("--hash32=",&local_500,0x20);
        uVar59 = (uint)local_500;
        iVar36 = 0;
        uVar54 = (uint)local_4fc;
        uVar56 = (uint)local_4fb;
        local_530 = 0;
        local_52c = 0;
        if (uVar59 == 0) {
          if (local_4ff == 0) {
LAB_0011842a:
            uVar37 = (uint)local_4fe;
            if (uVar37 == 0) {
LAB_00118434:
              uVar37 = (uint)local_4fd;
              if (uVar37 == 0) {
LAB_0011843e:
                if (uVar54 == 0) {
LAB_00118444:
                  if (uVar56 == 0) {
LAB_0011844a:
                    if (local_4fa == 0) {
LAB_00118452:
                      if ((local_4f9 != 0) && ((local_4f9 & 0x80) == 0)) {
                        if ((local_4f9 & 0x40) != 0) {
                          iVar36 = 0x38;
                          goto LAB_0011912c;
                        }
                        if ((local_4f9 & 0x20) != 0) {
                          iVar36 = 0x38;
LAB_00119576:
                          uVar37 = iVar36 + 2;
                          goto LAB_001186ec;
                        }
                        if ((local_4f9 & 0x10) != 0) {
                          uVar37 = 0x38;
                          goto LAB_00119676;
                        }
                        if ((local_4f9 & 8) != 0) {
                          iVar36 = 0x38;
LAB_0011968e:
                          uVar37 = iVar36 + 4;
                          goto LAB_001186ec;
                        }
                        if ((local_4f9 & 4) != 0) {
                          uVar37 = 0x38;
                          goto LAB_0011969e;
                        }
                        if ((local_4f9 & 2) != 0) {
                          iVar36 = 0x38;
                          goto LAB_001196b6;
                        }
                        if ((local_4f9 & 1) != 0) {
                          iVar36 = 0x38;
                          goto LAB_001186ea;
                        }
                      }
                    }
                    else if ((local_4fa & 0x80) == 0) {
                      if ((local_4fa & 0x40) == 0) {
                        if ((local_4fa & 0x20) != 0) {
                          iVar36 = 0x30;
                          goto LAB_00119576;
                        }
                        if ((local_4fa & 0x10) != 0) {
                          uVar37 = 0x30;
                          goto LAB_00119676;
                        }
                        if ((local_4fa & 8) != 0) {
                          iVar36 = 0x30;
                          goto LAB_0011968e;
                        }
                        if ((local_4fa & 4) != 0) {
                          uVar37 = 0x30;
                          goto LAB_0011969e;
                        }
                        if ((local_4fa & 2) == 0) {
                          if ((local_4fa & 1) != 0) {
                            iVar36 = 0x30;
                            goto LAB_001186ea;
                          }
                          goto LAB_00118452;
                        }
                        iVar36 = 0x30;
LAB_001196b6:
                        uVar37 = iVar36 + 6;
                      }
                      else {
                        uVar37 = 0x31;
                      }
                      goto LAB_001186ec;
                    }
                  }
                  else if (-1 < (int)(uVar56 << 0x18)) {
                    if ((int)(uVar56 << 0x19) < 0) {
                      uVar37 = 0x29;
                    }
                    else if ((int)(uVar56 << 0x1a) < 0) {
                      uVar37 = 0x2a;
                    }
                    else if ((int)(uVar56 << 0x1b) < 0) {
                      uVar37 = 0x2b;
                    }
                    else if ((int)(uVar56 << 0x1c) < 0) {
                      uVar37 = 0x2c;
                    }
                    else if ((int)(uVar56 << 0x1d) < 0) {
                      uVar37 = 0x2d;
                    }
                    else {
                      if (-1 < (int)(uVar56 << 0x1e)) {
                        if ((int)(uVar56 << 0x1f) < 0) {
                          iVar36 = 0x28;
                          goto LAB_001186ea;
                        }
                        goto LAB_0011844a;
                      }
                      uVar37 = 0x2e;
                    }
                    goto LAB_001186ec;
                  }
                  goto LAB_0011845a;
                }
                if (-1 < (int)(uVar54 << 0x18)) {
                  if ((int)(uVar54 << 0x19) < 0) {
                    uVar37 = 0x21;
                  }
                  else if ((int)(uVar54 << 0x1a) < 0) {
                    uVar37 = 0x22;
                  }
                  else if ((int)(uVar54 << 0x1b) < 0) {
                    uVar37 = 0x23;
                  }
                  else if ((int)(uVar54 << 0x1c) < 0) {
                    uVar37 = 0x24;
                  }
                  else if ((int)(uVar54 << 0x1d) < 0) {
                    uVar37 = 0x25;
                  }
                  else {
                    if (-1 < (int)(uVar54 << 0x1e)) {
                      if ((int)(uVar54 << 0x1f) < 0) {
                        iVar36 = 0x20;
                        goto LAB_001186ea;
                      }
                      goto LAB_00118444;
                    }
                    uVar37 = 0x26;
                  }
                  goto LAB_001186ec;
                }
              }
              else if (-1 < (int)(uVar37 << 0x18)) {
                if ((int)(uVar37 << 0x19) < 0) {
                  uVar37 = 0x19;
                }
                else if ((int)(uVar37 << 0x1a) < 0) {
                  uVar37 = 0x1a;
                }
                else if ((int)(uVar37 << 0x1b) < 0) {
                  uVar37 = 0x1b;
                }
                else if ((int)(uVar37 << 0x1c) < 0) {
                  uVar37 = 0x1c;
                }
                else if ((int)(uVar37 << 0x1d) < 0) {
                  uVar37 = 0x1d;
                }
                else {
                  if (-1 < (int)(uVar37 << 0x1e)) {
                    if ((int)(uVar37 << 0x1f) < 0) {
                      iVar36 = 0x18;
                      goto LAB_001186ea;
                    }
                    goto LAB_0011843e;
                  }
                  uVar37 = 0x1e;
                }
                goto LAB_001186ec;
              }
            }
            else if (-1 < (int)(uVar37 << 0x18)) {
              if ((int)(uVar37 << 0x19) < 0) {
                uVar37 = 0x11;
              }
              else if ((int)(uVar37 << 0x1a) < 0) {
                uVar37 = 0x12;
              }
              else if ((int)(uVar37 << 0x1b) < 0) {
                uVar37 = 0x13;
              }
              else if ((int)(uVar37 << 0x1c) < 0) {
                uVar37 = 0x14;
              }
              else if ((int)(uVar37 << 0x1d) < 0) {
                uVar37 = 0x15;
              }
              else {
                if (-1 < (int)(uVar37 << 0x1e)) {
                  if ((int)(uVar37 << 0x1f) < 0) {
                    iVar36 = 0x10;
                    goto LAB_001186ea;
                  }
                  goto LAB_00118434;
                }
                uVar37 = 0x16;
              }
              goto LAB_001186ec;
            }
LAB_00118490:
            if (uVar59 != 0) goto LAB_001184c4;
          }
          else if (-1 < (int)((uint)local_4ff << 0x18)) {
joined_r0x00118c5a:
            if ((int)((uint)local_4ff << 0x19) < 0) {
              iVar36 = 8;
              goto LAB_0011912c;
            }
            uVar37 = (uint)local_4ff;
            if ((int)(uVar37 << 0x1a) < 0) {
              uVar37 = 10;
            }
            else if ((int)(uVar37 << 0x1b) < 0) {
              uVar37 = 0xb;
            }
            else if ((int)(uVar37 << 0x1c) < 0) {
              uVar37 = 0xc;
            }
            else if ((int)(uVar37 << 0x1d) < 0) {
              uVar37 = 0xd;
            }
            else {
              if (-1 < (int)(uVar37 << 0x1e)) {
                if ((int)(uVar37 << 0x1f) < 0) {
                  iVar36 = 8;
                  goto LAB_001186ea;
                }
                goto LAB_0011842a;
              }
              uVar37 = 0xe;
            }
            goto LAB_001186ec;
          }
          if (((local_4ff == 0) && (local_4fe == 0)) &&
             (local_4fd == 0 &&
              (uint)local_4f9 + ((uint)local_4fa + (uVar56 + uVar54 * 0x100) * 0x100) * 0x100 <
              uVar42)) {
            pcVar29 = "!!!!!!!!!!! right !!!!!!!!!!!!";
            DAT_0019f044 = DAT_0011a654;
            goto LAB_0011a416;
          }
        }
        else if (-1 < (int)(uVar59 << 0x18)) {
          if ((local_500 & 0x40) == 0) {
            uVar37 = uVar59 & 0x20;
            if ((local_500 & 0x20) == 0) {
              if ((local_500 & 0x10) == 0) {
                uVar37 = uVar59 & 8;
                if ((local_500 & 8) == 0) {
                  if ((int)(uVar59 << 0x1d) < 0) {
LAB_0011969e:
                    uVar37 = uVar37 + 5;
                  }
                  else if ((int)(uVar59 << 0x1e) < 0) {
                    uVar37 = 6;
                  }
                  else {
                    if (-1 < (int)(uVar59 << 0x1f)) {
                      if (local_4ff == 0) goto LAB_0011842a;
                      if (-1 < (int)((uint)local_4ff << 0x18)) goto joined_r0x00118c5a;
                      goto LAB_001184c4;
                    }
                    iVar36 = 0;
LAB_001186ea:
                    uVar37 = iVar36 + 7;
                  }
                }
                else {
                  uVar37 = (uVar59 & 0x10) + 4;
                }
              }
              else {
LAB_00119676:
                uVar37 = uVar37 + 3;
              }
            }
            else {
              uVar37 = (uVar59 & 0x40) + 2;
            }
          }
          else {
LAB_0011912c:
            uVar37 = iVar36 + 1;
          }
LAB_001186ec:
          if (0x21 < uVar37) {
LAB_0011845a:
            uVar37 = (uint)DAT_00195644;
            HintPreloadData(&DAT_0019f028 + iVar31 * 8);
            iVar36 = *(int *)(&DAT_00195494 + uVar37 * 4);
            (&DAT_0019f020)[iVar31] = (double)(&DAT_0019f020)[iVar31] + 1.0;
            *(int *)(&DAT_00195494 + uVar37 * 4) = iVar36 + 1;
          }
          goto LAB_00118490;
        }
LAB_001184c4:
        DAT_001957ac = DAT_001957ac + 1;
        printf("check again %d------\n",DAT_001957ac);
        memcpy(local_4c0,DAT_001187c4,0x50);
        local_478 = local_520;
        local_474 = uStack_51c;
        memset(&local_4e0,0,0x20);
        usleep(1000);
        FUN_001151a8(local_4c0,&DAT_0019af20,&local_4e0);
        uVar27 = local_4c5;
        uVar26 = local_4c9;
        uVar25 = local_4d0;
        uVar24 = local_4d2;
        uVar23 = local_4d3;
        uVar22 = local_4d4;
        uVar21 = local_4d5;
        uVar20 = local_4d6;
        uVar54 = local_4e0;
        bVar46 = (byte)local_4e0;
        uVar28 = local_4e0._1_1_;
        local_4e0._0_2_ = CONCAT11(local_4c2,local_4c1);
        local_4e0._2_1_ = SUB41(uVar54,2);
        uVar18 = local_4e0._2_1_;
        local_4c1 = bVar46;
        local_4c2 = uVar28;
        local_4e0._3_1_ = SUB41(uVar54,3);
        uVar28 = local_4e0._3_1_;
        local_4e0 = CONCAT13(local_4c4,CONCAT12(local_4c3,(undefined2)local_4e0));
        local_4c3 = uVar18;
        local_4c4 = uVar28;
        uVar28 = local_4dc._1_1_;
        uVar18 = local_4dc._2_1_;
        local_4c5 = (undefined)local_4dc;
        uVar19 = local_4dc._3_1_;
        local_4dc._0_3_ = CONCAT12(local_4c7,CONCAT11(local_4c6,uVar27));
        local_4c7 = uVar18;
        local_4dc = CONCAT13(local_4c8,(undefined3)local_4dc);
        local_4c8 = uVar19;
        local_4c6 = uVar28;
        uVar28 = local_4d8._1_1_;
        local_4c9 = (undefined)local_4d8;
        local_4d8 = CONCAT11(local_4ca,uVar26);
        local_4ca = uVar28;
        local_4d6 = local_4cb;
        local_4cb = uVar20;
        local_4d5 = local_4cc;
        local_4cc = uVar21;
        local_4d4 = local_4cd;
        local_4cd = uVar22;
        local_4d3 = local_4ce;
        local_4ce = uVar23;
        local_4d2 = local_4cf;
        local_4d0 = local_4d1;
        local_4d1 = uVar25;
        local_4cf = uVar24;
        FUN_0011b120("--hash32=",&local_4e0,0x20);
        uVar56 = local_4e0 & 0xff;
        uVar59 = local_4dc & 0xff;
        uVar54 = local_4dc >> 8 & 0xff;
        uVar37 = local_4dc >> 0x10 & 0xff;
        if (uVar56 == 0) {
          if (local_4e0._1_1_ == 0) {
LAB_001185da:
            uVar44 = (uint)local_4e0._2_1_;
            if (uVar44 == 0) {
LAB_001185e2:
              uVar44 = (uint)local_4e0._3_1_;
              if (uVar44 == 0) {
LAB_001185e8:
                if (uVar59 == 0) {
LAB_001185ee:
                  if (uVar54 == 0) {
LAB_001185f4:
                    if (uVar37 == 0) {
LAB_001185fc:
                      if ((local_4dc >> 0x18 != 0) && ((local_4dc & 0x80000000) == 0)) {
                        if ((local_4dc & 0x40000000) != 0) {
                          iVar36 = 0x38;
                          goto LAB_00119140;
                        }
                        if ((local_4dc & 0x20000000) != 0) {
                          iVar36 = 0x38;
LAB_0011957e:
                          uVar44 = iVar36 + 2;
                          goto LAB_001186b2;
                        }
                        if ((local_4dc & 0x10000000) != 0) {
                          uVar44 = 0x38;
                          goto LAB_0011967e;
                        }
                        if ((local_4dc & 0x8000000) != 0) {
                          iVar36 = 0x38;
LAB_00119696:
                          uVar44 = iVar36 + 4;
                          goto LAB_001186b2;
                        }
                        if ((local_4dc & 0x4000000) != 0) {
                          uVar44 = 0x38;
                          goto LAB_001196ae;
                        }
                        if ((local_4dc & 0x2000000) != 0) {
                          iVar36 = 0x38;
                          goto LAB_001196c6;
                        }
                        if ((local_4dc & 0x1000000) != 0) {
                          uVar44 = 0x38;
                          goto LAB_001186b0;
                        }
                      }
                    }
                    else if ((local_4dc & 0x800000) == 0) {
                      if ((local_4dc & 0x400000) == 0) {
                        if ((local_4dc & 0x200000) != 0) {
                          iVar36 = 0x30;
                          goto LAB_0011957e;
                        }
                        if ((local_4dc & 0x100000) != 0) {
                          uVar44 = 0x30;
                          goto LAB_0011967e;
                        }
                        if ((local_4dc & 0x80000) != 0) {
                          iVar36 = 0x30;
                          goto LAB_00119696;
                        }
                        if ((local_4dc & 0x40000) != 0) {
                          uVar44 = 0x30;
                          goto LAB_001196ae;
                        }
                        if ((local_4dc & 0x20000) == 0) {
                          if ((local_4dc & 0x10000) != 0) {
                            uVar44 = 0x30;
                            goto LAB_001186b0;
                          }
                          goto LAB_001185fc;
                        }
                        iVar36 = 0x30;
LAB_001196c6:
                        uVar44 = iVar36 + 6;
                      }
                      else {
                        uVar44 = 0x31;
                      }
                      goto LAB_001186b2;
                    }
                  }
                  else if (-1 < (int)(uVar54 << 0x18)) {
                    if ((int)(uVar54 << 0x19) < 0) {
                      uVar44 = 0x29;
                    }
                    else if ((int)(uVar54 << 0x1a) < 0) {
                      uVar44 = 0x2a;
                    }
                    else if ((int)(uVar54 << 0x1b) < 0) {
                      uVar44 = 0x2b;
                    }
                    else if ((int)(uVar54 << 0x1c) < 0) {
                      uVar44 = 0x2c;
                    }
                    else if ((int)(uVar54 << 0x1d) < 0) {
                      uVar44 = 0x2d;
                    }
                    else {
                      if (-1 < (int)(uVar54 << 0x1e)) {
                        if ((int)(uVar54 << 0x1f) < 0) {
                          uVar44 = 0x28;
                          goto LAB_001186b0;
                        }
                        goto LAB_001185f4;
                      }
                      uVar44 = 0x2e;
                    }
                    goto LAB_001186b2;
                  }
                  goto LAB_00118604;
                }
                if (-1 < (int)(uVar59 << 0x18)) {
                  if ((int)(uVar59 << 0x19) < 0) {
                    uVar44 = 0x21;
                  }
                  else if ((int)(uVar59 << 0x1a) < 0) {
                    uVar44 = 0x22;
                  }
                  else if ((int)(uVar59 << 0x1b) < 0) {
                    uVar44 = 0x23;
                  }
                  else if ((int)(uVar59 << 0x1c) < 0) {
                    uVar44 = 0x24;
                  }
                  else if ((int)(uVar59 << 0x1d) < 0) {
                    uVar44 = 0x25;
                  }
                  else {
                    if (-1 < (int)(uVar59 << 0x1e)) {
                      if ((int)(uVar59 << 0x1f) < 0) {
                        uVar44 = 0x20;
                        goto LAB_001186b0;
                      }
                      goto LAB_001185ee;
                    }
                    uVar44 = 0x26;
                  }
                  goto LAB_001186b2;
                }
              }
              else if (-1 < (int)(uVar44 << 0x18)) {
                if ((int)(uVar44 << 0x19) < 0) {
                  uVar44 = 0x19;
                }
                else if ((int)(uVar44 << 0x1a) < 0) {
                  uVar44 = 0x1a;
                }
                else if ((int)(uVar44 << 0x1b) < 0) {
                  uVar44 = 0x1b;
                }
                else if ((int)(uVar44 << 0x1c) < 0) {
                  uVar44 = 0x1c;
                }
                else if ((int)(uVar44 << 0x1d) < 0) {
                  uVar44 = 0x1d;
                }
                else {
                  if (-1 < (int)(uVar44 << 0x1e)) {
                    if ((int)(uVar44 << 0x1f) < 0) {
                      uVar44 = 0x18;
                      goto LAB_001186b0;
                    }
                    goto LAB_001185e8;
                  }
                  uVar44 = 0x1e;
                }
                goto LAB_001186b2;
              }
            }
            else if (-1 < (int)(uVar44 << 0x18)) {
              if ((int)(uVar44 << 0x19) < 0) {
                uVar44 = 0x11;
              }
              else if ((int)(uVar44 << 0x1a) < 0) {
                uVar44 = 0x12;
              }
              else if ((int)(uVar44 << 0x1b) < 0) {
                uVar44 = 0x13;
              }
              else if ((int)(uVar44 << 0x1c) < 0) {
                uVar44 = 0x14;
              }
              else if ((int)(uVar44 << 0x1d) < 0) {
                uVar44 = 0x15;
              }
              else {
                if (-1 < (int)(uVar44 << 0x1e)) {
                  if ((int)(uVar44 << 0x1f) < 0) {
                    uVar44 = 0x10;
                    goto LAB_001186b0;
                  }
                  goto LAB_001185e2;
                }
                uVar44 = 0x16;
              }
              goto LAB_001186b2;
            }
LAB_00118620:
            if (uVar56 != 0) goto LAB_0011864e;
          }
          else if (-1 < (int)((uint)local_4e0._1_1_ << 0x18)) {
joined_r0x00118cd2:
            if ((int)((uint)local_4e0._1_1_ << 0x19) < 0) {
              iVar36 = 8;
LAB_00119140:
              uVar44 = iVar36 + 1;
            }
            else {
              uVar44 = (uint)local_4e0._1_1_;
              if ((int)(uVar44 << 0x1a) < 0) {
                uVar44 = 10;
              }
              else if ((int)(uVar44 << 0x1b) < 0) {
                uVar44 = 0xb;
              }
              else if ((int)(uVar44 << 0x1c) < 0) {
                uVar44 = 0xc;
              }
              else if ((int)(uVar44 << 0x1d) < 0) {
                uVar44 = 0xd;
              }
              else {
                if (-1 < (int)(uVar44 << 0x1e)) {
                  if ((int)(uVar44 << 0x1f) < 0) {
                    uVar44 = 8;
                    goto LAB_001186b0;
                  }
                  goto LAB_001185da;
                }
                uVar44 = 0xe;
              }
            }
            goto LAB_001186b2;
          }
          if (((local_4e0._1_1_ == 0) && (local_4e0._2_1_ == 0)) &&
             (local_4e0._3_1_ == 0 &&
              (local_4dc >> 0x18) + (uVar37 + (uVar54 + uVar59 * 0x100) * 0x100) * 0x100 < uVar42))
          {
            pcVar29 = "!!!!!!!!!!! right !!!!!!!!!!! again ";
            DAT_0019f044 = DAT_0011a500;
LAB_0011a416:
            puts(pcVar29);
            local_52c = CONCAT11((undefined)local_478,local_478._1_1_);
            local_530._0_2_ = CONCAT11((undefined)local_474,local_474._1_1_);
            local_530 = CONCAT22(CONCAT11((char)(local_478 >> 0x10),local_478._3_1_),
                                 (undefined2)local_530);
            FUN_0001b02c(iVar38 + 0x17c,&local_530,6);
            DAT_00195794 = DAT_00195794 + 1;
            printf("commit_stat=%d\n",DAT_00195794);
            return 1;
          }
        }
        else if (-1 < (int)(uVar56 << 0x18)) {
          if ((local_4e0 & 0x40) == 0) {
            uVar44 = local_4e0 & 0x20;
            if ((local_4e0 & 0x20) == 0) {
              if ((local_4e0 & 0x10) == 0) {
                uVar44 = local_4e0 & 8;
                if ((local_4e0 & 8) == 0) {
                  if ((local_4e0 & 4) == 0) {
                    uVar44 = local_4e0 & 2;
                    if ((local_4e0 & 2) == 0) {
                      if (-1 < (int)(uVar56 << 0x1f)) {
                        if (local_4e0._1_1_ == 0) goto LAB_001185da;
                        if (-1 < (int)((uint)local_4e0._1_1_ << 0x18)) goto joined_r0x00118cd2;
                        goto LAB_0011864e;
                      }
LAB_001186b0:
                      uVar44 = uVar44 + 7;
                    }
                    else {
                      uVar44 = (local_4e0 & 4) + 6;
                    }
                  }
                  else {
LAB_001196ae:
                    uVar44 = uVar44 + 5;
                  }
                }
                else {
                  uVar44 = (local_4e0 & 0x10) + 4;
                }
              }
              else {
LAB_0011967e:
                uVar44 = uVar44 + 3;
              }
            }
            else {
              uVar44 = (local_4e0 & 0x40) + 2;
            }
          }
          else {
            uVar44 = 1;
          }
LAB_001186b2:
          if (0x21 < uVar44) {
LAB_00118604:
            iVar36 = (uint)DAT_00195644 * 4;
            *(int *)(&DAT_00195494 + iVar36) = *(int *)(&DAT_00195494 + iVar36) + 1;
            *(int *)(&DAT_001957b0 + iVar36) = *(int *)(&DAT_001957b0 + iVar36) + 1;
          }
          goto LAB_00118620;
        }
LAB_0011864e:
        iVar36 = (uint)DAT_00195644 * 4;
        DAT_00195b1c = DAT_00195b1c + 1;
        *(int *)(&DAT_001958d4 + iVar36) = *(int *)(&DAT_001958d4 + iVar36) + 1;
        *(int *)(&DAT_001959f8 + iVar36) = *(int *)(&DAT_001959f8 + iVar36) + 1;
        printf("err_diff=%d\n");
      }
      iVar31 = iVar31 + 1;
      iVar47 = iVar47 + 0x14;
      dVar67 = DAT_00118248;
      dVar69 = DAT_00118240;
    } while (iVar31 != 4);
    usleep(5000);
  } while( true );
}


