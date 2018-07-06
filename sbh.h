class WorldObject {
  protected:
    bool isLive_;
    bool dirty_;
    ObjId objId_;
    Properties props_;
    mPixel lastXmp_;
    mPixel lastYmp_;
    Shape *shape_;
    const VidAnimData *vad_;
    int lastDamageT_;

  public:
    WorldObject(ObjId, const Properties &);
    WorldObject(ObjId, Properties *);
    static bool ptrCompare(const WorldObject *, const WorldObject *);
    ~WorldObject(int);
    virtual World * world() const;
    virtual SubWorld * subWorld() const;
    WorldId ownerId() const;
    ObjId objId() const;
    ObjKey key() const;
    const Properties & props() const;
    mPixel xmp() const;
    mPixel ymp() const;
    mPixel wmp() const;
    mPixel hmp() const;
    mPixel rmp() const;
    mPixel bmp() const;
    pixel x() const;
    pixel y() const;
    pixel w() const;
    pixel h() const;
    pixel r() const;
    pixel b() const;
    mPixel cxmp() const;
    mPixel cymp() const;
    mPixel cx() const;
    mPixel cy() const;
    Point<int> cmp() const;
    mPixel lastXmp() const;
    mPixel lastYmp() const;
    const Shape & shape() const;
    const VidAnimData * vad() const;
    int getAnimId(GeneralAnim) const;
    const AnimationData * animData(int *) const;
    bool getBoxVec(BoxType, std::vector<std::vector<Rectangle<int>>> *) const;
    bool getBoxes(BoxType, std::vector<Rectangle<int>> *) const;
    bool getPoints(PointType, std::vector<AnimPoint> *) const;
    void setEmitPosition(const AnimPoint &, WorldObject *) const;
    Rectangle<int> rect() const;
    Rectangle<int> rectmp() const;
    Point<int> center() const;
    bool blockTypeMove() const;
    virtual const char * interactName() const;
    virtual const ItemProperties * interactItemProps() const;
    std::string debugString();
    bool isLive() const;
    bool isDirty() const;
    void clearDirty();
    bool facingLeft() const;
    bool facingRight() const;
    PoseV posev() const;
    FullPose fullPose() const;
    bool flipV() const;
    int sinceDamage() const;
    int overlapPerc(mPixel, mPixel, mPixel, mPixel) const;
    mPixel distMovedSq() const;
    bool isGround() const;
    virtual const PropertyDesc * getPropertyDesc(Property);
    virtual const PropertyDesc * getPropertyDescByName(const char *);
    virtual bool clearProperty(Property);
    virtual bool setIntProperty(Property, int);
    virtual bool setBoolProperty(Property, bool);
    virtual bool setMessageProperty(Property, google::protobuf::MessageLite *);
    virtual bool setStringProperty(Property, const std::string &);
    virtual bool hasProperty(Property);
    virtual int getIntProperty(Property);
    virtual bool getBoolProperty(Property);
    virtual const google::protobuf::MessageLite * getMessageProperty(Property);
    virtual std::string getStringProperty(Property);
    virtual void onCreate();
    virtual void onInteract(WorldObject *, bool);
    virtual void onTrigger(WorldObject *);
    virtual void onTriggerEnd(WorldObject *);
    virtual void onShieldBlock(WorldObject *);
    virtual void onDamage(int, bool, bool, WorldId, int, int, const char *);
    virtual void onDestroy(DestroyReason);
    virtual void update(int, int);
    virtual void doDamage(int *, bool, int, const ObjKey &, int, int, const char *, int, int);
    virtual void destroy(bool, int, DestroyReason);
    virtual void sendDestroy(int, DestroyReason);
    virtual void addTime(int);
    virtual void addState(WorldState_World *);
    void doInteract(WorldObject *, bool);
    void doTrigger(WorldObject *);
    void doTriggerEnd(WorldObject *);
    virtual void doReaction(const Reaction &, WorldObject *);
    virtual bool onGround();
    virtual bool onLedge();
  protected:
    void setVid(const char *);
    bool doLinearMove(Linear *, mPixel, mPixel, int *);
    void doShieldBoxes(int);
    void pushR(mPixel *, mPixel, mPixel, mPixel) const;
    void pushL(mPixel *, mPixel, mPixel, mPixel) const;
    void pushD(mPixel, mPixel *, mPixel, mPixel) const;
    void pushU(mPixel, mPixel *, mPixel, mPixel) const;
}


class NativeObject : public WorldObject {
  protected:
    int offsetDT_;
    uPixel xVel_;
    uPixel yVel_;
    bool isPrivate_;
    bool hasGravity_;
    bool xBlocked_;
    bool yBlocked_;
    bool crouching_;
    bool running_;
    uPixel attXVel_;
    uPixel moveXVel_;
    uPixel moveYVel_;
    uPixel walkAccel_;
    bool instantWalkDecel_;
    uPixel airAccel_;
    uPixel gravityAccel_;
    std::unordered_map<ObjKey, int> damaged_;
    int redamageTime_;
    std::string createSound_;
    bool createSoundGlobal_;
  private:
    ObjKey attached_;

  public:
    NativeObject(ObjId, const Properties &);
    ~NativeObject(int);
    int offsetDT() const;
    bool isPrivate() const;
    WorldObject * getAttached();
    TerrainType attachedTerrainType();
    void setAttached(WorldObject *);
    AnimId setAnim(GeneralAnim, int, int, bool);
    void setAnimId(AnimId, int, int, bool);
    bool xBlocked() const;
    bool yBlocked() const;
    void setXVel(uPixel);
    void setYVel(uPixel);
    uPixel xVel() const;
    uPixel yVel() const;
    void setCreateSound(const char *, bool);
    const std::string & createSound() const;
    bool hasGravity();
    void setHasGravity(bool);
    virtual void update(int, int);
    virtual bool clearProperty(Property);
    virtual bool setIntProperty(Property, int);
    virtual bool setBoolProperty(Property, bool);
    virtual bool setMessageProperty(Property, google::protobuf::MessageLite *);
    virtual bool setStringProperty(Property, const std::string &);
    virtual void playSound(const char *, SoundType, bool);
    virtual void onCreate();
    virtual void destroy(bool, int, DestroyReason);
    virtual void addTime(int);
    virtual void addState(WorldState_World *);
    virtual void doReaction(const Reaction &, WorldObject *);
    virtual bool onGround();
    virtual bool onLedge();
    bool isClimbing();
    bool grabClimbWall();
    bool grabLadder(bool);
    void getPlayerHitBoxHits(const std::vector<Rectangle<int>> &, const std::unordered_map<ObjKey, int> &, std::vector<std::pair<WorldObject*, Point<int> >> *);
  protected:
    virtual bool internalUpdate(int, int);
    virtual bool canBeDamaged(int);
    virtual int calculateGravity();
    virtual bool hasPlayerDamage();
    virtual bool hasPlayerHitBoxDamage();
    virtual uint getPlayerDamage(bool *, int *);
    void setMoveTo(mPixel, mPixel, int);
    bool isSimpleMoveTo(const Linear &);
    void addWalkTime(int);
    void addClimbTime(int);
    void addLadderTime(int);
    void addAirTime(int);
    void setPose();
    void blockedModifyMove(mPixel *, mPixel *);
    void updatePose();
    void internalAddTime(int);
    bool playerOwnerUpdate(int, int);
    bool findPlayerDamage(WorldObject **, int *, IntPoint *, bool *);
    bool playerIsHit(WorldObject *, int, IntPoint *);
    void playerDoDamage(WorldObject *, int, const IntPoint &);
}


class ClientObject : public NativeObject {
  protected:
    ClientSubWorld *subWorld_;
    Action *action_;

  public:
    ClientObject(ClientSubWorld *, ObjId, const Properties &);
    ~ClientObject(int);
    virtual ClientWorld * world() const;
    virtual SubWorld * subWorld() const;
    ClientSubWorld * clientSubWorld();
    virtual void onShieldBlock(WorldObject *);
    virtual bool canDoAction();
    Action * action();
    void doAction(Action *);
    void cancelAction();
    virtual void setMovement(int);
    virtual bool isLoot();
  protected:
    virtual bool internalUpdate(int, int);
}

class Player : public ClientObject {
  protected:
    uint32 numStash_;
    uint32 numCharSlots_;
    uint32 deeds_;
    ObjKey interactObj_;
    std::vector<ObjKey> activeTriggers_;    
    std::unordered_map<int, CharacterProperties*, std::hash<int>, std::equal_to<int>, std::allocator<std::pair<int const, CharacterProperties*> > > slottedCharProps_;

  public:
    Player(ClientSubWorld *, const CreatePlayer &);
    ~Player(int);
    virtual void onDestroy(DestroyReason);
    virtual void doReaction(const Reaction &, WorldObject *);
    virtual int playerType();
    virtual PlayerCharacter * character();
    virtual const char * name();
    virtual bool hasStash(int);
    virtual bool hasCharSlot(int);
    virtual void updateProps(AccountProperties *, CharacterProperties *) const;
    virtual void modifyHitpoints(int, bool, bool);
    virtual void doInput(WorldInput, WorldInput, WorldInput);
    virtual bool canEquip(const ItemDescription &);
    virtual bool canApply(const ItemDescription &);
    virtual bool equipItem(const ItemProperties &);
    virtual bool addItem(const ItemProperties &);
    virtual bool hasSlotPos(SlotPos);
    virtual SlotPos getEmptySlotPos(Slot);
    virtual bool moveItem(SlotPos, SlotPos);
    virtual bool dropItem(SlotPos);
    virtual int getNumPos(Slot);
    virtual Item * getItem(SlotPos);
    virtual ObjKey interactObj();
    virtual void applyBoost(const StatBoost &);
    virtual const CharacterDescription * charDesc();
    virtual bool canRejoin();
    virtual bool canHome();
    virtual int homeCountdown();
    virtual int mk();
    virtual int avgMK100();
    virtual int getStat(Stat);
    virtual uint32 deeds();
    virtual int maxLevel() const;
    void addSlottedCharProps(const CharacterProperties &);
    const CharacterProperties * slottedCharProps(int);
  protected:
    void doActivates(int);
}
