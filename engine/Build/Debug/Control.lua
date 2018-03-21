

function init(self)
    GetRendererComponent(self):getMaterial():setDiffuseColor(Vector4.new(1, 0, 1, 1));
    Get3DPhysicsComponent(self):setGravity(Vector3.new(0, -9.8, 0))
    Get3DPhysicsComponent(self):applyGravity()
    Get3DPhysicsComponent(self):setMass(20)
    Get3DPhysicsComponent(self):setRestitution(0);
    AddEvent(self, "onCollision");
    self:setAttributei("hasChanged", 0)
end

function update(self)
    local input = STGame:Get():getInput()
    local delta = STGame:Get():getDelta()
    local oldX = self:transform():getTranslate():getX()
    local oldY = self:transform():getTranslate():getY()
    local oldZ = self:transform():getTranslate():getZ()
    local rotY = self:transform():getRotate():getY()
    local physHandle = Get3DPhysicsComponent(self)
    local animHandle = Get3DAnimationComponent(self)

    if oldY < -5.0 then
        Remove(self)
    end

    if input:isKeyDown(KEY.KEY_J) then
        oldZ = oldZ + (0.025 * delta)
        self:transform():setTranslate(Vector3.new(oldX, oldY, oldZ))
        physHandle:updateTransform()
    end

    if input:isKeyDown(KEY.KEY_L) then
        oldZ = oldZ - (0.025 * delta)
        self:transform():setTranslate(Vector3.new(oldX, oldY, oldZ))
        physHandle:updateTransform()
    end

    if input:isKeyDown(KEY.KEY_I) then
        oldX = oldX + (0.025 * delta)
        self:transform():setTranslate(Vector3.new(oldX, oldY, oldZ))
        physHandle:updateTransform()
    end

    if input:isKeyDown(KEY.KEY_K) then
        oldX = oldX - (0.025 * delta)
        self:transform():setTranslate(Vector3.new(oldX, oldY, oldZ))
        physHandle:updateTransform()
    end

    if input:isKeyDown(KEY.KEY_O) then
        rotY = rotY - (0.25 * delta)
        self:transform():setRotateY(rotY)
        physHandle:updateTransform()
    end

    if input:isKeyDown(KEY.KEY_U) then
        rotY = rotY + (0.25 * delta)
        self:transform():setRotateY(rotY)
        physHandle:updateTransform()
    end

    if input:isKeyPressed(KEY.KEY_SPACE) then
        physHandle:applyForce(Vector3.new(0, 60, 0))
    end

    if input:isKeyPressed(KEY.KEY_R) then
        local r = math.random()
        local g = math.random()
        local b = ( r / g) * math.random()
        GetRendererComponent(self):getMaterial():setDiffuseColor(Vector4.new(r, g, b, 1))
    end
end

function onCollision(self, other)
    if self:getAttributei("hasChanged") == 0 then
        self:setAttributei("hasChanged", 1)
        local r = math.random()
        local g = math.random()
        local b = math.random()
        GetRendererComponent(self):getMaterial():setDiffuseColor(Vector4.new(r,g,b, 1))
		GetRendererComponent(self):getMaterial():setMetallicF(0.0)
		GetRendererComponent(self):getMaterial():setRoughnessF(0.0)
    end
end
