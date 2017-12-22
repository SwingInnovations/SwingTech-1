function start(self)
    addEvent(self, "onCollision");
end

function update(self)
    local input = STGame:Get():getInput()
    local phys = get3DPhysicsComponent(self)
    local downForce = Vector3.new(0, -20, 0)

    if input:isKeyPressed(KEY.KEY_R) then
        self:transform():setTranslateX(1)
        self:transform():setTranslateY(10);
        self:transform():setTranslateZ(2);
        phys:updateTransform()
        phys:toggleFreeze(false)
        phys:setActive(true)
        phys:applyForce(downForce)
        phys:applyGravity()
    end
end

function onCollision(self, other)
    print("Collided with: " .. other:getTag())
end