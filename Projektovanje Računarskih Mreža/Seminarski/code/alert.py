class Alert:
    def __init__(self, attributes):
        self.id = attributes.get('alertid', "")
        
        self.date = attributes.get('date', "")
        self.time = attributes.get('time', "")
        self.sessionDuration = attributes.get('sessionduration', "")
        
        self.sourceSpoofed = attributes.get('spoofed', "")
        self.sourceAddrressCategory = attributes.get('category', "")
        self.sourceAddress = attributes.get('address', "")
        self.sourcePort = attributes.get('sport', "")
        
        self.destinationAddressCategory = attributes.get('Address category', "")
        self.destinationAddress = attributes.get('Address address', "")
        self.destinationPort = attributes.get('dport', "")
        
        self.service = attributes.get('Service name', "")
        
        self.impact = attributes.get('impact', "")
        
    def getVector(self):
        return (self.id,
                self.date,
                self.time,
                self.sessionDuration,
                self.sourceSpoofed,
                self.sourceAddrressCategory,
                self.sourceAddress,
                self.sourcePort,
                self.destinationAddressCategory,
                self.destinationAddress,
                self.destinationPort,
                self.service,
                self.impact)