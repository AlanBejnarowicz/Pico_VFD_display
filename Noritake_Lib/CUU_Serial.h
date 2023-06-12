class CUU_Serial : public CUU_Interface {
protected:
    unsigned SIO_PIN:4;
    unsigned SCK_PIN:4;
    unsigned STB_PIN:4;

public:
    CUU_Serial(uint8_t sio, uint8_t stb, uint8_t sck):
        SIO_PIN(sio), STB_PIN(stb), SCK_PIN(sck)
    {
    }
    
    void init() {
    	_delay_ms(500);

		INIT(SIO_PIN);
		INIT(SCK_PIN);
		INIT(STB_PIN);
        
        RAISE(SIO_PIN);
        RAISE(SCK_PIN);
        RAISE(STB_PIN);
        
        DIRECTION(SIO_PIN, 1);
        DIRECTION(SCK_PIN, 1);
        DIRECTION(STB_PIN, 1);

        write(0x30,false);  // 8-bit function set
    	write(0x30,false);  // 8-bit function set
    	write(0x30,false);  // 8-bit function set
    	write(0x30,false);  // 8-bit function set
    }
    void write(uint8_t data, bool rs) {
    	uint8_t	x = 0xf8 + 2*rs, i=0x80;
    	
    	LOWER(STB_PIN);
    	for ( ; i; i>>=1) {
            LOWER(SCK_PIN);
    		if (x & i)
    			RAISE(SIO_PIN);
    		else
    			LOWER(SIO_PIN);
    		RAISE(SCK_PIN);
    	}
    	
    	x = data;
    	for (i=0x80; i; i>>=1) {
    		LOWER(SCK_PIN);
    		if (x & i)
    			RAISE(SIO_PIN);
    		else
    			LOWER(SIO_PIN);
    		RAISE(SCK_PIN);
    	}
    	RAISE(STB_PIN);
    }
    uint8_t read(bool rs) {
    	uint8_t	i=0x80, data = 0xfc + 2*rs;
    
    	LOWER(STB_PIN);
    	for ( ; i; i>>=1) {
    		LOWER(SCK_PIN);
    		if (data & i)
    			RAISE(SIO_PIN);
    		else
    			LOWER(SIO_PIN);
    		RAISE(SCK_PIN);
    	}
    
        DIRECTION(SIO_PIN, 0);
    	_delay_us(1);
    	
    	for (i=0; i<8; i++) {
    		LOWER(SCK_PIN);
    		data <<= 1;
    		RAISE(SCK_PIN);
    		if (CHECK(SIO_PIN))
    			data |= 1;
    	}
    
    	RAISE(STB_PIN);
    	DIRECTION(SIO_PIN, 1);
    	return data;
    }
    bool is8bit() { return true; };
};