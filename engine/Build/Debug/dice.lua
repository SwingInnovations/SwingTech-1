function start(self)
    addEvent(self, "onCollision");
end

function update(self)
    local input = STGame:Get():getInput()
    local phys = get3DPhysicsComponent(self)

    if input:isKeyPressed(KEY.KEY_R) then
        getGraphicsComponent(self):getMaterial():setDiffuseColor(Vector4.new(1, 0, 0, 1));
        self:transform():setTranslateX(1)
        self:transform():setTranslateY(10);
        self:transform():setTranslateZ(2);
        phys:updateTransform()
        phys:toggleFreeze(false)
        phys:setActive(true)
        phys:applyForce(Vector3.new(0, -20, 0))
        phys:applyGravity()
    end
end

function onCollision(self, other)
    print("Collided with: " .. other:getTag())
    local gfx = getGraphicsComponent(self)
    gfx:getMaterial():setDiffuseColor(Vector4.new(0, 1, 0, 1))
end