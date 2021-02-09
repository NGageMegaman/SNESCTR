#include "executionUnit.h"
using namespace std;

ExecutionUnit::ExecutionUnit() {
    regfile = Regfile::getInstance();
    arithlogicUnit = ArithlogicUnit::getInstance();
    branchUnit = BranchUnit::getInstance();
    memopUnit = MemopUnit::getInstance();
    procStatUnit = ProcStatUnit::getInstance();
}

ExecutionUnit *ExecutionUnit::executionUnit = nullptr;

ExecutionUnit *ExecutionUnit::getInstance() {
    if (executionUnit == nullptr) {
        executionUnit = new ExecutionUnit();
    }
    return executionUnit;
}

void ExecutionUnit::execute(inst_t inst, longw operand, longw address) {
    //THIS MUST BE SUBSTITUTED SOMEHOW WITH A MAP OR STH
    switch (inst) {
        case ADC1: case ADC2: case ADC3: case ADC4: case ADC5:
        case ADC6: case ADC7: case ADC8: case ADC9: case ADCa:
        case ADCb: case ADCc: case ADCd: case ADCe: case ADCf:
            arithlogicUnit->ADC(operand, address);
            break;
        case AND1: case AND2: case AND3: case AND4: case AND5:
        case AND6: case AND7: case AND8: case AND9: case ANDa:
        case ANDb: case ANDc: case ANDd: case ANDe: case ANDf:
            arithlogicUnit->AND(operand, address);
            break;
        case ASL2:
            arithlogicUnit->ASL_A(operand, address);
            break;
        case ASL1: case ASL3: case ASL4: case ASL5:
            arithlogicUnit->ASL_mem(operand, address);
            break;
        case BCC:
            branchUnit->BCC(operand, address);
            break;
        case BCS:
            branchUnit->BCS(operand, address);
            break;
        case BEQ:
            branchUnit->BEQ(operand, address);
            break;
        case BIT1: case BIT2: case BIT3: case BIT4:
            procStatUnit->BIT(operand, address);
            break;
        case BIT5:
            procStatUnit->BIT_imm(operand, address);
            break;
        case BMI:
            branchUnit->BMI(operand, address);
            break;
        case BNE:
            branchUnit->BNE(operand, address);
            break;
        case BPL:
            branchUnit->BPL(operand, address);
            break;
        case BRA:
            branchUnit->BRA(operand, address);
            break;
        case BRK:
            procStatUnit->BRK(operand, address);
            break;
        case BRL:
            branchUnit->BRL(operand, address);
            break;
        case BVC:
            branchUnit->BVC(operand, address);
            break;
        case BVS:
            branchUnit->BVS(operand, address);
            break;
        case CLC:
            procStatUnit->CLC(operand, address);
            break;
        case CLD:
            procStatUnit->CLD(operand, address);
            break;
        case CLI:
            procStatUnit->CLI(operand, address);
            break;
        case CLV:
            procStatUnit->CLV(operand, address);
            break;
        case CMP1: case CMP2: case CMP3: case CMP4: case CMP5:
        case CMP6: case CMP7: case CMP8: case CMP9: case CMPa:
        case CMPb: case CMPc: case CMPd: case CMPe: case CMPf:
            arithlogicUnit->CMP(operand, address);
            //HOTFIX, THIS IS APU COMM PROTOCOL
            if (address == 0x2140) {
                regfile->writeP(PFlags_t::ZERO_FLAG, true);
                regfile->writeP(PFlags_t::OVERFLOW_FLAG, false);
            }
            break;
        case COP:
            procStatUnit->COP(operand, address);
            break;
        case CPX1: case CPX2: case CPX3:
            arithlogicUnit->CPX(operand, address);
            break;
        case CPY1: case CPY2: case CPY3:
            arithlogicUnit->CPY(operand, address);
            break;
        case DEC2: case DEC3: case DEC4: case DEC5:
            arithlogicUnit->DEC_mem(operand, address);
            break;
        case DEC1:
            arithlogicUnit->DEC_A(operand, address);
            break;
        case DEX:
            arithlogicUnit->DEX(operand, address);
            break;
        case DEY:
            arithlogicUnit->DEY(operand, address);
            break;
        case EOR1: case EOR2: case EOR3: case EOR4: case EOR5:
        case EOR6: case EOR7: case EOR8: case EOR9: case EORa:
        case EORb: case EORc: case EORd: case EORe: case EORf:
            arithlogicUnit->EOR(operand, address);
            break;
        case INC2: case INC3: case INC4: case INC5:
            arithlogicUnit->INC_mem(operand, address);
            break;
        case INC1:
            arithlogicUnit->INC_A(operand, address);
            break;
        case INX:
            arithlogicUnit->INX(operand, address);
            break;
        case INY:
            arithlogicUnit->INY(operand, address);
            break;
        case JMP1: case JMP3: case JMP4:
            branchUnit->JMP(operand, address);
            break;
        case JMP2: case JMP5:
            branchUnit->JML(operand, address);
            break;
        case JSR1: case JSR2:
            branchUnit->JSR(operand, address);
	        break;
        case JSL:
            branchUnit->JSL(operand, address);
	        break;
        case LDA1: case LDA2: case LDA3: case LDA4: case LDA5:
        case LDA6: case LDA7: case LDA8: case LDA9: case LDAa:
        case LDAb: case LDAc: case LDAd: case LDAe: case LDAf:
            memopUnit->LDA(operand, address);
	        break;
        case LDX1: case LDX2: case LDX3: case LDX4: case LDX5:
            memopUnit->LDX(operand, address);
            break;
        case LDY1: case LDY2: case LDY3: case LDY4: case LDY5:
            memopUnit->LDY(operand, address);
            break;
        case LSR1: case LSR3: case LSR4: case LSR5:
            arithlogicUnit->LSR_mem(operand, address);
            break;
        case LSR2:
            arithlogicUnit->LSR_A(operand, address);
            break;
        case MVN:
            memopUnit->MVN(operand, address);
            break;
        case MVP:
            memopUnit->MVP(operand, address);
            break;
        case ORA1: case ORA2: case ORA3: case ORA4: case ORA5:
        case ORA6: case ORA7: case ORA8: case ORA9: case ORAa:
        case ORAb: case ORAc: case ORAd: case ORAe: case ORAf:
            arithlogicUnit->ORA(operand, address);
	        break;
        case PEA:
            memopUnit->PEA(operand, address);
            break;
        case PEI:
            memopUnit->PEI(operand, address);
            break;
        case PER:
            memopUnit->PER(operand, address);
            break;
        case PHA:
            memopUnit->PHA(operand, address);
	        break;
        case PHB:
            memopUnit->PHB(operand, address);
            break;
        case PHD:
            memopUnit->PHD(operand, address);
            break;
        case PHK:
            memopUnit->PHK(operand, address);
            break;
        case PHP:
            memopUnit->PHP(operand, address);
            break;
        case PHX:
            memopUnit->PHX(operand, address);
            break;
        case PHY:
            memopUnit->PHY(operand, address);
            break;
        case PLA:
            memopUnit->PLA(operand, address);
            break;
        case PLB:
            memopUnit->PLB(operand, address);
            break;
        case PLD:
            memopUnit->PLD(operand, address);
            break;
        case PLP:
            memopUnit->PLP(operand, address);
            break;
        case PLX:
            memopUnit->PLX(operand, address);
            break;
        case PLY:
            memopUnit->PLY(operand, address);
            break;
        case REP:
            procStatUnit->REP(operand, address);
            break;
        case ROL1: case ROL3: case ROL4: case ROL5:
            arithlogicUnit->ROL_mem(operand, address);
            break;
        case ROL2:
            arithlogicUnit->ROL_A(operand, address);
            break;
        case ROR1: case ROR3: case ROR4: case ROR5:
            arithlogicUnit->ROR_mem(operand, address);
            break;
        case ROR2:
            arithlogicUnit->ROR_A(operand, address);
            break;
        case RTI:
            branchUnit->RTI(operand, address);
            break;
        case RTL:
            branchUnit->RTL(operand, address);
            break;
        case RTS:
            branchUnit->RTS(operand, address);
            break;
        case SBC1: case SBC2: case SBC3: case SBC4: case SBC5:
        case SBC6: case SBC7: case SBC8: case SBC9: case SBCa:
        case SBCb: case SBCc: case SBCd: case SBCe: case SBCf:
            arithlogicUnit->SBC(operand, address);
            break;
        case SEC:
            procStatUnit->SEC(operand, address);
            break;
        case SED:
            procStatUnit->SED(operand, address);
            break;
        case SEI:
            procStatUnit->SEI(operand, address);
            break;
        case SEP:
            procStatUnit->SEP(operand, address);
            break;
        case STA1: case STA2: case STA3: case STA4: case STA5:
        case STA6: case STA7: case STA8: case STA9: case STAa:
        case STAb: case STAc: case STAd: case STAe:
            memopUnit->STA(operand, address);
	        break;
        case STP:
            procStatUnit->STP(operand, address);
            break;
        case STX1: case STX2: case STX3:
            memopUnit->STX(operand, address);
            break;
        case STY1: case STY2: case STY3:
            memopUnit->STY(operand, address);
            break;
        case STZ1: case STZ2: case STZ3: case STZ4:
            memopUnit->STZ(operand, address);
	        break;
        case TAX:
            procStatUnit->TAX(operand, address);
            break;
        case TAY:
            procStatUnit->TAY(operand, address);
            break;
        case TCD:
            procStatUnit->TCD(operand, address);
            break;
        case TCS:
            procStatUnit->TCS(operand, address);
            break;
        case TDC:
            procStatUnit->TDC(operand, address);
            break;
        case TRB1: case TRB2:
            memopUnit->TRB(operand, address);
            break;
        case TSB1: case TSB2:
            memopUnit->TSB(operand, address);
            break;
        case TSC:
            procStatUnit->TSC(operand, address);
            break;
        case TSX:
            procStatUnit->TSX(operand, address);
            break;
        case TXA:
            procStatUnit->TXA(operand, address);
            break;
        case TXS:
            procStatUnit->TXS(operand, address);
            break;
        case TXY:
            procStatUnit->TXY(operand, address);
            break;
        case TYA:
            procStatUnit->TYA(operand, address);
	        break;
        case TYX:
            procStatUnit->TYX(operand, address);
            break;
        case WAI:
            procStatUnit->WAI(operand, address);
            break;
        case WDM:
            procStatUnit->WDM(operand, address);
            break;
        case XBA:
            procStatUnit->XBA(operand, address);
            break;
        case XCE:
            procStatUnit->XCE(operand, address);
            break;
    	default : 
            procStatUnit->NOP(operand, address);
    }
}