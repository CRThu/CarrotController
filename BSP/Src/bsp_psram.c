#include "bsp_psram.h"

#ifdef BSP_PSRAM_OCTOSPI
    uint8_t buffer[8192];
    XSPI_RegularCmdTypeDef sCommand = { 0 };
#endif

void bsp_psram_reset()
{
    #ifdef BSP_PSRAM_SPI
    uint8_t cmd = 0x66;
    HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&BSP_PSRAM_SPI, &cmd, 1, 0xFFFF);
    HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);
    cmd = 0x99;
    HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&BSP_PSRAM_SPI, &cmd, 1, 0xFFFF);
    HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);
    #endif
    #ifdef BSP_PSRAM_OCTOSPI


    /* RESET ENABLE */

    /* Initialize the read register command */
    sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction = 0x66;
    sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address = 0x000000;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
    sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode = HAL_XSPI_DATA_NONE;
    sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength = 1;
    sCommand.DummyCycles = 0;
    sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;


    /* Configure the command */
    if (HAL_XSPI_Command(&hospi1, &sCommand, 1000) != HAL_OK)
    {
        //return HAL_ERROR;
        write_msg("RESET ENABLE CMD ERR\r\n");
    }

    delay_ns(100);

    /* RESET */

    /* Initialize the read register command */
    sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction = 0x99;
    sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address = 0x000000;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
    sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode = HAL_XSPI_DATA_NONE;
    sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength = 1;
    sCommand.DummyCycles = 0;
    sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;


    /* Configure the command */
    if (HAL_XSPI_Command(&hospi1, &sCommand, 1000) != HAL_OK)
    {
        //return HAL_ERROR;
        write_msg("RESET CMD ERR\r\n");
    }

    delay_ns(100);


    #endif
}

uint8_t bsp_psram_ping()
{
    #ifdef BSP_PSRAM_SPI
    /* RX: 07 00 00 00 0D 5D 53 15 3C 6D 71 AA 0D 5D */
    uint8_t eid[14] = { 0 };
    eid[0] = 0x9F;
    HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&BSP_PSRAM_SPI, eid, eid, sizeof(eid), 0xFFFF);
    HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);
    return (eid[5] == 0x5D);
    #endif

    #ifdef BSP_PSRAM_OCTOSPI
    #endif

    return 0x00;
}


int8_t bsp_psram_read(uint32_t addr, uint8_t* data, uint32_t size)
{
    #ifdef BSP_PSRAM_SPI
    uint8_t prefix[5] = { 0 };

    uint32_t curr_addr = addr;
    uint32_t curr_size = 0;
    uint32_t remain_size = size;

    while (remain_size > 0)
    {
        if (curr_addr % 1024 == 0)
        {
            // aligned
            curr_size = remain_size >= 1024 ? 1024 : remain_size;
        }
        else
        {
            // unaligned
            curr_size = (remain_size >= (1024 - curr_addr % 1024)) ? (1024 - curr_addr % 1024) : remain_size;
        }

        prefix[0] = 0x0B;
        prefix[1] = curr_addr >> 16;
        prefix[2] = curr_addr >> 8;
        prefix[3] = curr_addr;
        prefix[4] = 0x00;

        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&BSP_PSRAM_SPI, prefix, sizeof(prefix), 0xFFFF);
        //HAL_SPI_Receive(&BSP_PSRAM_SPI, data, curr_size, 0xFFFF);
        HAL_SPI_Receive_DMA(&BSP_PSRAM_SPI, data, curr_size);

        // wait for transfer
        uint32_t tickstart = HAL_GetTick();
        while (HAL_SPI_GetState(&BSP_PSRAM_SPI) != HAL_SPI_STATE_READY)
        {
            if ((HAL_GetTick() - tickstart) >= BSP_PSRAM_TIMEOUT)
            {
                return -2;
            }
        }

        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);

        remain_size -= curr_size;
        curr_addr += curr_size;
        data += curr_size;
    }
    return 0;
    #endif
    #ifdef BSP_PSRAM_OCTOSPI
    #endif
    return -1;
}

int8_t bsp_psram_write(uint32_t addr, uint8_t* data, uint32_t size)
{
    #ifdef BSP_PSRAM_SPI
    uint8_t prefix[4] = { 0 };

    uint32_t curr_addr = addr;
    uint32_t curr_size = 0;
    uint32_t remain_size = size;

    while (remain_size > 0)
    {
        if (curr_addr % 1024 == 0)
        {
            // aligned
            curr_size = remain_size >= 1024 ? 1024 : remain_size;
        }
        else
        {
            // unaligned
            curr_size = (remain_size >= (1024 - curr_addr % 1024)) ? (1024 - curr_addr % 1024) : remain_size;
        }

        prefix[0] = 0x02;
        prefix[1] = curr_addr >> 16;
        prefix[2] = curr_addr >> 8;
        prefix[3] = curr_addr;

        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&BSP_PSRAM_SPI, prefix, sizeof(prefix), 0xFFFF);
        //HAL_SPI_Transmit(&BSP_PSRAM_SPI, data, curr_size, 0xFFFF);
        HAL_SPI_Transmit_DMA(&BSP_PSRAM_SPI, data, curr_size);

        // wait for transfer
        uint32_t tickstart = HAL_GetTick();
        while (HAL_SPI_GetState(&BSP_PSRAM_SPI) != HAL_SPI_STATE_READY)
        {
            if ((HAL_GetTick() - tickstart) >= BSP_PSRAM_TIMEOUT)
            {
                return -2;
            }
        }

        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);

        remain_size -= curr_size;
        curr_addr += curr_size;
        data += curr_size;
    }
    return 0;
    #endif
    #ifdef BSP_PSRAM_OCTOSPI
    #endif
    return -1;
}


#if(CARROT_CONTROLLER_HW == STM32H563_CONTROLLER)

void psram_test()
{
    uint32_t psram_test[2000] = { 0 };
    uint8_t psram_status = bsp_psram_ping();
    write_msg("psram status: %d\r\n", psram_status);
    for (int i = 0; i < sizeof(psram_test) / sizeof(uint32_t); i++)
        psram_test[i] = i;
    psram_status = bsp_psram_write(100, (uint8_t*)psram_test, sizeof(psram_test));
    if (psram_status != 0) write_msg("bsp_psram_write error code: %d\r\n", psram_status);
    memset(psram_test, 0, sizeof(psram_test));
    psram_status = bsp_psram_read(100, (uint8_t*)psram_test, sizeof(psram_test));
    if (psram_status != 0) write_msg("bsp_psram_write error code: %d\r\n", psram_status);
    uint32_t err = 0;
    for (int i = 0; i < sizeof(psram_test) / sizeof(uint32_t); i++)
        if (psram_test[i] != i)
            err++;
    write_msg("psram test error num: %d\r\n", err);
}

#else

void psram_test()
{

    uint8_t buffer[8192];
    XSPI_RegularCmdTypeDef sCommand = { 0 };


    /* RESET ENABLE */

    /* Initialize the read register command */
    sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction = 0x66;
    sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address = 0x000000;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
    sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode = HAL_XSPI_DATA_NONE;
    sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength = 1;
    sCommand.DummyCycles = 0;
    sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;


    /* Configure the command */
    if (HAL_XSPI_Command(&hospi1, &sCommand, 1000) != HAL_OK)
    {
        //return HAL_ERROR;
        write_msg("RESET ENABLE CMD ERR\r\n");
    }

    delay_ns(100);

    /* RESET */

    /* Initialize the read register command */
    sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction = 0x99;
    sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address = 0x000000;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
    sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode = HAL_XSPI_DATA_NONE;
    sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength = 1;
    sCommand.DummyCycles = 0;
    sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;


    /* Configure the command */
    if (HAL_XSPI_Command(&hospi1, &sCommand, 1000) != HAL_OK)
    {
        //return HAL_ERROR;
        write_msg("RESET CMD ERR\r\n");
    }

    delay_ns(100);

    /* READ ID */

    /* Initialize the read register command */
    sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction = 0x9F;
    sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address = 0x000000;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_1_LINE;
    sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode = HAL_XSPI_DATA_1_LINE;
    sCommand.DataLength = 8 * 2;
    sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DummyCycles = 0;
    sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

    /* Configure the command */
    if (HAL_XSPI_Command(&hospi1, &sCommand, 1000) != HAL_OK)
    {
        //return HAL_ERROR;
        write_msg("READ ID CMD ERR\r\n");
    }

    /* Reception of the data */
    if (HAL_XSPI_Receive(&hospi1, (uint8_t*)buffer, 1000) != HAL_OK)
    {
        //return HAL_ERROR;
        write_msg("READ ID RECV ERR\r\n");
    }

    write_msg("PSRAM0\r\n");
    write_msg("MFID=%02X\r\n", buffer[0]);
    write_msg("KGD =%02X\r\n", buffer[2]);
    write_msg("EID =%02X%02X%02X%02X%02X%02X\r\n", buffer[4], buffer[6], buffer[8], buffer[10], buffer[12], buffer[14]);

    write_msg("PSRAM1\r\n");
    write_msg("MFID=%02X\r\n", buffer[1]);
    write_msg("KGD =%02X\r\n", buffer[3]);
    write_msg("EID =%02X%02X%02X%02X%02X%02X\r\n", buffer[5], buffer[7], buffer[9], buffer[11], buffer[13], buffer[15]);
}


#endif